/**
 * Author: Yuhao Yao
 * Date: 24-01-08
 * Description: Segment tree. Point apply and thus no lazy propogation.
 *  Always define an \textbf{info\_apply} function for class \textbf{Info} you use to tell segment tree how you apply modification.
 *  Combine is set as plus so if you just let T be numerical type then you have range sum in the info and as range query result. To have something different, say rangeMin, define a struct with constructer and + operation.
 * Time: O(\log N) per operation.
 * Status: tested on https://qoj.ac/contest/695/problem/1856, https://codeforces.com/gym/411278/problem/G.
 */
template<class Info>
struct Segtree {
	#define ls i * 2 /// start-hash
	#define rs i * 2 + 1

	int n; 
	vector<Info> info;

	Segtree(int n) : n(n) {
		assert(n > 0);
		info.resize(4 << __lg(n));
	}
	Segtree(const vector<Info> &init) : Segtree(sz(init)) {
		auto build = [&](auto &dfs, int i, int l, int r) {
			if (l == r) {
				info[i] = init[l];
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, ls, l, mid);
			dfs(dfs, rs, mid + 1, r);
			pull(i);
		};
		build(build, 1, 0, n - 1);
	}
private:
	void pull(int i) { info[i] = info[ls] + info[rs]; }
public:
	template<class... T>
	void point_apply(int p, const T&... val) {
		auto dfs = [&](auto &dfs, int i, int l, int r) {
			if (l == r) {
				info_apply(info[i], val...);
				return;
			}
			int mid = (l + r) >> 1;
			if (p <= mid) dfs(dfs, ls, l, mid);
			else dfs(dfs, rs, mid + 1, r);
			pull(i);
		};
		dfs(dfs, 1, 0, n - 1);
	} /// end-hash

	Info range_ask(int ql, int qr) { /// start-hash
		Info res{};
		auto dfs = [&](auto &dfs, int i, int l, int r) {
			if (qr < l || r < ql) return;
			if (ql <= l && r <= qr) {
				res = res + info[i];
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, ls, l, mid);
			dfs(dfs, rs, mid + 1, r);
		};
		dfs(dfs, 1, 0, n - 1);
		return res;
	} /// end-hash
	
	int find_first(int ql, int qr, function<bool(const Info&, int, int)> func) { /// start-hash
		auto dfs = [&](auto &dfs, int i, int l, int r) {
			if (qr < l || r < ql || (ql <= l && r <= qr && func(info[i], l, r) == 0)) return -1;
			if (l == r) return l;

			int mid = (l + r) >> 1;
			int res = dfs(dfs, ls, l, mid);
			if (res != -1) return res;
			else return dfs(dfs, rs, mid + 1, r);
		};
		return dfs(dfs, 1, 0, n - 1);
	}; /// end-hash
	int find_last(int ql, int qr, function<bool(const Info&, int, int)> func) { /// start-hash
		auto dfs = [&](auto &dfs, int i, int l, int r) {
			if (qr < l || r < ql || (ql <= l && r <= qr && func(info[i], l, r) == 0)) return -1;
			if (l == r) return l;

			int mid = (l + r) >> 1;
			int res = dfs(dfs, rs, mid + 1, r);
			if (res != -1) return res;
			else return dfs(dfs, ls, l, mid);
		};
		return dfs(dfs, 1, 0, n - 1);
	}; /// end-hash
	#undef ls
	#undef rs
};
