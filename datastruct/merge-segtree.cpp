/**
 * Author: Yuhao Yao
 * Date: 23-01-13
 * Description: Merge Segment Tree. pointApply creates nodes when nodes are missing.
 * Time: O(\log n) for pointApply, rangeAsk; Amortized O(\log n) for Merge.
 * Status: tested on https://codeforces.com/gym/415469/problem/J.
 */
template<class Info>
struct MergeSegTree {
	struct node {
		using ptr = shared_ptr<node>;
		Info info;
		ptr ls, rs;
		node(Info _info = {}): info(_info), ls(nullptr), rs(nullptr) {}
		void pull() {
			info = (ls == nullptr ? Info{} : ls->info) + (rs == nullptr ? Info{} : rs->info);
		}
	};
	using ptr = typename node::ptr;
private:
	int n;
	ptr rt;
public:
	MergeSegTree(int n, const ptr &_rt = nullptr): n(n), rt(_rt) { assert(n > 0); }

	friend MergeSegTree merge(const MergeSegTree &t1, MergeSegTree &t2, function<Info(const Info&, const Info&)> func) { // t2 will be empty after merge.
		auto dfs = [&](auto &dfs, const ptr &a, ptr &b, int l, int r) -> ptr {
			if (a == nullptr) return b;
			if (b == nullptr) return a;
			if (l == r) {
				a->info = func(a->info, b->info);
				b = nullptr;
				return a;
			}
			int mid = (l + r) >> 1;
			a->ls = dfs(dfs, a->ls, b->ls, l, mid);
			a->rs = dfs(dfs, a->rs, b->rs, mid + 1, r);
			a->pull();
			b = nullptr;
			return a;
		};
		assert(t1.n == t2.n);
		return MergeSegTree(t1.n, dfs(dfs, t1.rt, t2.rt, 0, t1.n - 1));
	}
	// I have to have the argument n in all kinds of Apply and Ask...
	template<class... T>
	void pointApply(int p, const T&... val) {
		auto dfs = [&](auto &dfs, ptr &now, int l, int r) -> void {
			if (now == nullptr) now = make_shared<node>();
			if (l == r) {
				InfoApply(now->info, val...);
				return;
			}
			int mid = (l + r) >> 1;
			if (p <= mid) dfs(dfs, now->ls, l, mid);
			else dfs(dfs, now->rs, mid + 1, r);
			now->pull();
		};
		dfs(dfs, rt, 0, n - 1);
	}

	Info rangeAsk(int ql, int qr) {
		Info res{};
		auto dfs = [&](auto &dfs, const ptr &now, int l, int r) -> void {
			if (qr < l || r < ql || now == nullptr) return;
			if (ql <= l && r <= qr) {
				res = res + now->info;
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, now->ls, l, mid);
			dfs(dfs, now->rs, mid + 1, r);
		};
		dfs(dfs, rt, 0, n - 1);
		return res;
	}

	int findFirst(int ql, int qr, function<bool(const Info&, int, int)> func) {
		auto dfs = [&](auto &dfs, ptr &now, int l, int r) {
			if (qr < l || r < ql || (ql <= l && r <= qr && func(now == nullptr ? Info{} : now->info, l, r) == 0)) return -1;
			if (l == r) return l;
			if (now == nullptr) return max(ql, l);

			int mid = (l + r) >> 1;
			int res = dfs(dfs, now->ls, l, mid);
			if (res != -1) return res;
			else return dfs(dfs, now->rs, mid + 1, r);
		};
		return dfs(dfs, rt, 0, n - 1);
	};
};