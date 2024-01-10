/**
 * Author: Yuhao Yao
 * Date: 24-01-07
 * Description: Merge Lazy Segment Tree. \textbf{point\_apply} creates nodes when nodes are missing. \textbf{range\_apply} only applies to existing nodes.
 * Time: O(\log n) for point\_apply, range\_apply, range\_ask; Amortized O(\log n) for Merge.
 * Status: tested on https://codeforces.com/contest/1455/problem/G.
 */
template<class Info, class Tag>
struct MergeLazySegtree {
	struct node {
		Info info;
		Tag tag;
		unique_ptr<node> ls, rs;
		node() : info{}, tag{}, ls{}, rs{} {}
		void pull() {
			info = (ls ? ls->info : Info{}) + (rs ? rs->info : Info{});
		}
		template<class... T>
		void apply(int l, int r, const T&... val) {
			info_apply(info, l, r, val...);
			tag_apply(tag, l, r, val...);
		}
		void push(int l, int r) {
			if (tag != Tag{}) {
				int mid = (l + r) >> 1;
				if (ls) ls->apply(l, mid, tag);
				if (rs) rs->apply(mid + 1, r, tag);
				tag = {};
			}
		}
	};
	using ptr = unique_ptr<node>;
	int n;
	ptr rt;

	MergeLazySegtree(int n) : n(n), rt{} { assert(n > 0); }
	
	void join(MergeLazySegtree &rhs, function<Info(const Info&, const Info&)> merge) {
		auto dfs = [&](auto &dfs, ptr &a, ptr &b, int l, int r) {
			if (b == nullptr) return;
			if (a == nullptr) {
				swap(a, b);
				return;
			}
			if (l == r) {
				a->info = merge(a->info, b->info);
				return;
			}
			a->push(l, r);
			b->push(l, r);
			int mid = (l + r) >> 1;
			dfs(dfs, a->ls, b->ls, l, mid);
			dfs(dfs, a->rs, b->rs, mid + 1, r);
			a->pull();
		};
		assert(n == rhs.n);
		dfs(dfs, rt, rhs.rt, 0, n - 1);
		rhs.rt = nullptr;
	}

	template<class... T>
	void point_apply(int p, const T&... val) {
		auto dfs = [&](auto &dfs, ptr &now, int l, int r) -> void {
			if (now == nullptr) now = make_unique<node>();
			if (l == r) {
				info_apply(now->info, val...);
				return;
			}
			now->push(l, r);
			int mid = (l + r) >> 1;
			if (p <= mid) dfs(dfs, now->ls, l, mid);
			else dfs(dfs, now->rs, mid + 1, r);
			now->pull();
		};
		dfs(dfs, rt, 0, n - 1);
	}

	template<class... T>
	void range_apply(int ql, int qr, const T&... val) {
		auto dfs = [&](auto &dfs, ptr &now, int l, int r) -> void {
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
		dfs(dfs, rt, 0, n - 1);
	}

	Info range_ask(int ql, int qr) {
		Info res{};
		auto dfs = [&](auto &dfs, ptr &now, int l, int r) -> void {
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
		dfs(dfs, rt, 0, n - 1);
		return res;
	}
};