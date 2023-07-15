/**
 * Author: Yuhao Yao
 * Date: 22-12-11
 * Description: Merge Lazy Segment Tree. pointApply creates nodes when nodes are missing.
 * Time: O(\log n) for pointApply, rangeApply, rangeAsk; Amortized O(\log n) for Merge.
 * Status: tested on https://codeforces.com/contest/1455/problem/G.
 */
template<class Info, class Tag>
class MergeLazySegTreeNode {
	using node = MergeLazySegTreeNode;
	node *ls, *rs;
	Info info;
	Tag tag;
public:
	MergeLazySegTreeNode(): ls(nullptr), rs(nullptr), info(Info{}), tag(Tag{}) {}
private:
	void pull() {
		info = (ls == nullptr ? Info{} : ls->info) + (rs == nullptr ? Info{} : rs->info);
	}
	
	template<class... T>
	void apply(int l, int r, const T&... val) {
		InfoApply(info, l, r, val...);
		TagApply(tag, l, r, val...);
	}

	void push(int l, int r) {
		if (tag != Tag{}) {
			int mid = (l + r) >> 1;
			if (ls != nullptr) ls->apply(l, mid, tag);
			if (rs != nullptr) rs->apply(mid + 1, r, tag);
			tag = {};
		}
	}
public:
	friend node* Merge(int n, node *r1, node *r2, function<Info(const Info&, const Info&)> func) {
		auto dfs = [&](auto &dfs, node *a, node *b, int l, int r) -> node* {
			if (a == nullptr) return b;
			if (b == nullptr) return a;
			if (l == r) {
				a->info = func(a->info, b->info);
				delete b;
				return a;
			}
			a->push(l, r);
			b->push(l, r);
			int mid = (l + r) >> 1;
			a->ls = dfs(dfs, a->ls, b->ls, l, mid);
			a->rs = dfs(dfs, a->rs, b->rs, mid + 1, r);
			a->pull();
			delete b;
			return a;
		};
		return dfs(dfs, r1, r2, 0, n - 1);
	}
	// I have to have the argument n in all kinds of Apply and Ask...
	template<class... T>
	friend void pointApply(node *&t, int n, int p, const T&... val) {
		auto dfs = [&](auto &dfs, node *&now, int l, int r) -> void {
			if (now == nullptr) now = new node;
			if (l == r) {
				InfoApply(now->info, val...);
				return;
			}
			now->push(l, r);
			int mid = (l + r) >> 1;
			if (p <= mid) dfs(dfs, now->ls, l, mid);
			else dfs(dfs, now->rs, mid + 1, r);
			now->pull();
		};
		dfs(dfs, t, 0, n - 1);
	}

	template<class... T>
	void rangeApply(int n, int ql, int qr, const T&... val) {
		auto dfs = [&](auto &dfs, node *now, int l, int r) -> void {
			if (qr < l || r < ql || now == nullptr) return;
			if (ql <= l && r <= qr) {
				now->apply(l, r, val...);
				return;
			}
			now->push(l, r);
			int mid = (l + r) >> 1;
			dfs(dfs, now->ls, l, mid);
			dfs(dfs, now->rs, mid + 1, r);
			now->pull();
		};
		dfs(dfs, this, 0, n - 1);
	}

	Info rangeAsk(int n, int ql, int qr) {
		Info res{};
		auto dfs = [&](auto &dfs, node *now, int l, int r) -> void {
			if (qr < l || r < ql || now == nullptr) return;
			if (ql <= l && r <= qr) {
				res = res + now->info;
				return;
			}
			now->push(l, r);
			int mid = (l + r) >> 1;
			dfs(dfs, now->ls, l, mid);
			dfs(dfs, now->rs, mid + 1, r);
		};
		dfs(dfs, this, 0, n - 1);
		return res;
	}
};