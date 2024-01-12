/**
 * Author: Yuhao Yao
 * Date: 24-01-07
 * Description: 2D Segment Tree of range $[oL, oR] \times [iL, iR]$. Point apply and thus no lazy propogation.
 *  Always define a global \textbf{info\_apply} function to tell segment tree how you apply modification. 
 *  Combine is set as + operation. If you use your own struct, then please define constructor and + operation.
 *  In constructor, $q$ is the number of \textbf{point\_apply} you will use. $oL$, $oR$, Note that range parameters can be negative.
 * Usage: Point Add and Range (Rectangle) Sum.
 *  void info_apply(int \&a, int b) { a += b; } // global
 *  ...
 *  SegTree2D<int> pseg(-5, 5, -5, 5, 1); // [-5, 5] * [-5, 5] and 1 update.
 *  int rt = 0; // empty node.
 *  rt = pseg.point_apply(rt, 2, -1, 1); // add 1 to position (2, -1).
 *  int sum = pseg.range_ask(rt, 3, 4, -2, -1); // ask the sum in rectangle [3, 4] * [-2, -1].
 * Time: O(\log (oR - oL + 1) \times \log(iR - iL + 1)) per operation.
 * Status: tested on https://qoj.ac/contest/819/problem/2548.
 */
template<class Info>
struct SegTree2D {
	struct iNode { Info info; int ls, rs; }; /// start-hash
	struct oNode { int id; int ls, rs; };
	
	int oL, oR, iL, iR;
	// change to array to accelerate, since allocating takes time. (saves ~ 200ms when allocating 1e7)
	vector<iNode> it;
	vector<oNode> ot;

	// node 0 is left as virtual empty node.
	SegTree2D(int oL, int oR, int iL, int iR, int q) : oL(oL), oR(oR), iL(iL), iR(iR), it(1), ot(1) {
		it.reserve(q * (__lg(oR - oL + 1) + 2) * (__lg(iR - iL + 1) + 2) + 1);
		ot.reserve(q * (__lg(oR - oL + 1) + 2) + 1);
	}

	// return new root id.
	template<class... T>
	int point_apply(int rt, int op, int ip, const T&... val) {
		auto idfs = [&](auto &dfs, int &i, int l, int r) {
			if (!i) {
				it.push_back({});
				i = sz(it) - 1;
			}
			if (l == r) {
				info_apply(it[i].info, val...);
				return;
			}
			int mid = (l + r) >> 1;
			auto &[info, ls, rs] = it[i];
			if (ip <= mid) dfs(dfs, ls, l, mid);
			else dfs(dfs, rs, mid + 1, r);
			info = it[ls].info + it[rs].info;
		};
		auto odfs = [&](auto &dfs, int &i, int l, int r) {
			if (!i) {
				ot.push_back({});
				i = sz(ot) - 1;
			}
			idfs(idfs, ot[i].id, iL, iR);
			if (l == r) return;
			int mid = (l + r) >> 1;
			if (op <= mid) dfs(dfs, ot[i].ls, l, mid);
			else dfs(dfs, ot[i].rs, mid + 1, r);
		};
		odfs(odfs, rt, oL, oR);
		return rt;
	} /// end-hash

	Info range_ask(int rt, int qol, int qor, int qil, int qir) { /// start-hash
		Info res{};
		auto idfs = [&](auto &dfs, int i, int l, int r) {
			if (!i || qir < l || r < qil) return;
			if (qil <= l && r <= qir) {
				res = res + it[i].info;
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, it[i].ls, l, mid);
			dfs(dfs, it[i].rs, mid + 1, r);
		};
		auto odfs = [&](auto &dfs, int i, int l, int r) {
			if (!i || qor < l || r < qol) return;
			if (qol <= l && r <= qor) {
				idfs(idfs, ot[i].id, iL, iR);
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, ot[i].ls, l, mid);
			dfs(dfs, ot[i].rs, mid + 1, r);
		};
		odfs(odfs, rt, oL, oR);
		return res;
	} /// end-hash
};
