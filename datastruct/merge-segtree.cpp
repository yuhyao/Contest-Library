/**
 * Author: Yuhao Yao
 * Date: 24-01-07
 * Description: Merge Segment Tree. point\_apply creates nodes when nodes are missing. Note that MergeSeg is not copyable and thus you can not write things like vector<MergeSegtree<int>> segs(n, n);
 * Time: O(\log n) for point\_apply, range\_ask; Amortized O(\log n) for Merge.
 * Status: tested on https://codeforces.com/gym/415469/problem/J.
*/
template<class Info>
struct MergeSegtree {
	struct node {
		Info info;
		unique_ptr<node> ls, rs;
		node(): info{}, ls{}, rs{} {}
		void pull() {
			info = (ls ? ls->info : Info{}) + (rs ? rs->info : Info{});
		}
	};
	using ptr = unique_ptr<node>;
	int n;
	ptr rt;

	MergeSegtree(int n): n(n), rt{} { assert(n > 0); }

	void join(MergeSegtree &rhs, function<Info(const Info&, const Info&)> merge) { // t2 will be empty after merge.
		auto dfs = [&](auto &dfs, ptr &a, ptr &b, int l, int r) -> void {
			if (b == nullptr) return;
			if (a == nullptr) {
				swap(a, b);
				return;
			}
			if (l == r) {
				a->info = merge(a->info, b->info);
				return;
			}
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
			int mid = (l + r) >> 1;
			if (p <= mid) dfs(dfs, now->ls, l, mid);
			else dfs(dfs, now->rs, mid + 1, r);
			now->pull();
		};
		dfs(dfs, rt, 0, n - 1);
	}

	Info range_ask(int ql, int qr) {
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

	int find_first(int ql, int qr, function<bool(const Info&, int, int)> func) {
		auto dfs = [&](auto &dfs, ptr &now, int l, int r) {
			if (qr < l || r < ql || (ql <= l && r <= qr && func(now ? now->info : Info{}, l, r) == false)) return -1;
			if (l == r) return l;
			if (now == nullptr) return func(Info{}, max(ql, l), min(qr, r)) ? max(ql, l) : -1;

			int mid = (l + r) >> 1;
			int res = dfs(dfs, now->ls, l, mid);
			if (res != -1) return res;
			else return dfs(dfs, now->rs, mid + 1, r);
		};
		return dfs(dfs, rt, 0, n - 1);
	}
};