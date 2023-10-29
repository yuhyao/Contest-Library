/**
 * Author: Yuhao Yao
 * Date: 23-10-28
 * Description: Dynamic Memory Allocated Segment Tree of range $[0, N - 1]$. Point apply and thus no lazy propogation.
 *  Always define a global $InfoApply$ function to tell segment tree how you apply modification. 
 *  Combine is set as + operation. If you use your own struct, then please define constructor and + operation.
 * Usage: Point Add and Range Sum.
 *  void InfoApply(int \&a, int b) { a += b; } // global
 *  ...
 *  DynamicSegtree<int> seg(1e9); // N = 1e9.
 *  seg.point_apply(100000, 2);
 * Time: O(\log N) per operation.
 * Status: tested on https://qoj.ac/contest/1399/problem/7641.
 */
template<class Info>
struct DynamicSegtree {
	struct node { Info info; int ls, rs; };
	int n;
	vector<node> ts;
	// node 0 is left as virtual empty node.
	DynamicSegtree(int n): n(n), ts(2) {
		assert(n > 0);
	}

	template<class... T>
	void point_apply(int pos, const T&... val) {
		auto dfs = [&](auto &dfs, int i, int l, int r) -> int {
			if (i == 0) {
				ts.push_back(node{});
				i = sz(ts) - 1;
			}

			if (l == r) {
				InfoApply(ts[i].info, val...);
				return i;
			}
			int mid = (l + r) >> 1;
			if (pos <= mid) ts[i].ls = dfs(dfs, ts[i].ls, l, mid);
			else ts[i].rs = dfs(dfs, ts[i].rs, mid + 1, r);
			ts[i].info = ts[ts[i].ls].info + ts[ts[i].rs].info;
			return i;
		};
		dfs(dfs, 1, 0, n - 1);
	}

	Info range_ask(int ql, int qr) {
		Info res{};
		auto dfs = [&](auto &dfs, int i, int l, int r) {
			if (i == 0 || qr < l || r < ql) return;
			if (ql <= l && r <= qr) {
				res = res + ts[i].info;
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, ts[i].ls, l, mid);
			dfs(dfs, ts[i].rs, mid + 1, r);
		};
		dfs(dfs, 1, 0, n - 1);
		return res;
	}
};
