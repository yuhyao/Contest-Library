/**
 * Author: Yuhao Yao
 * Date: 23-04-01
 * Description: Segment tree with lazy propogation.
 * Usage: Always define functions \textbf{InfoApply} and \textbf{TagApply} to tell segment tree how you apply modification.
 *  Combine is set as plus so if you just let T be numerical type then you have range sum in the info and as range query result. To have something different, say rangeMin, define a struct with constructer and + operation.
 * Time: O(\log N) per operation.
 * Status: tested on https://codeforces.com/gym/103371/problem/M.
 */
template<class Info, class Tag> class LazySegTree {
	#define ls i * 2
	#define rs i * 2 + 1

	int n;
	vector<Info> info;
	vector<Tag> tag;
public:
	LazySegTree(int n): n(n) {
		assert(n > 0);
		info.resize(4 << __lg(n));
		tag.resize(4 << __lg(n));
	}
	LazySegTree(const vector<Info> &init): LazySegTree(sz(init)) {
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

	template<class... T>
	void apply(int i, int l, int r, const T&... val) {
		InfoApply(info[i], l, r, val...);
		TagApply(tag[i], l, r, val...);
	}

	void push(int i, int l, int r) {
		if (tag[i] == Tag{}) return;
		int mid = (l + r) >> 1;
		apply(ls, l, mid, tag[i]);
		apply(rs, mid + 1, r, tag[i]);
		tag[i] = {};
	}
public:
	template<class... T>
	void rangeApply(int ql, int qr, const T&... val) {
		auto dfs = [&](auto &dfs, int i, int l, int r) {
			if (qr < l || r < ql) return;
			if (ql <= l && r <= qr) {
				apply(i, l, r, val...);
				return;
			}
			push(i, l, r);
			int mid = (l + r) >> 1;
			dfs(dfs, ls, l, mid);
			dfs(dfs, rs, mid + 1, r);
			pull(i);
		};
		dfs(dfs, 1, 0, n - 1);
	}

	Info rangeAsk(int ql, int qr) {
		Info res{};
		auto dfs = [&](auto &dfs, int i, int l, int r) {
			if (qr < l || r < ql) return;
			if (ql <= l && r <= qr) {
				res = res + info[i];
				return;
			}
			push(i, l, r);
			int mid = (l + r) >> 1;
			dfs(dfs, ls, l, mid);
			dfs(dfs, rs, mid + 1, r);
		};
		dfs(dfs, 1, 0, n - 1);
		return res;
	}

	int findFirst(int ql, int qr, function<bool(const Info&, int, int)> func) {
		auto dfs = [&](auto &dfs, int i, int l, int r) {
			if (qr < l || r < ql || (ql <= l && r <= qr && func(info[i], l, r) == 0)) return -1;
			if (l == r) return l;

			push(i, l, r);
			int mid = (l + r) >> 1;
			int res = dfs(dfs, ls, l, mid);
			if (res != -1) return res;
			else return dfs(dfs, rs, mid + 1, r);
		};
		return dfs(dfs, 1, 0, n - 1);
	};

	int findLast(int ql, int qr, function<bool(const Info&, int, int)> func) {
		auto dfs = [&](auto &dfs, int i, int l, int r) {
			if (qr < l || r < ql || (ql <= l && r <= qr && func(info[i], l, r) == 0)) return -1;
			if (l == r) return l;

			push(i, l, r);
			int mid = (l + r) >> 1;
			int res = dfs(dfs, rs, mid + 1, r);
			if (res != -1) return res;
			else return dfs(dfs, ls, l, mid);
		};
		return dfs(dfs, 1, 0, n - 1);
	};

	#undef ls
	#undef rs
};