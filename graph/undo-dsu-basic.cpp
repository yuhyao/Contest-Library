/**
 * Author: Yuhao Yao
 * Date: 23-05-01
 * Description: Undoable Disjoint Union Set for set ${0, ..., N - 1}$. 
 *  Use $top = top()$ to get a save point; use $undo(top)$ to go back to the save point.
 * Usage: 
 *  UndoDSU dsu(n);
 *  ...
 *  int top = dsu.top(); // get a save point.
 *  ... // do merging and other calculating here.
 *  dsu.undo(top); // get back to the save point.
 * Time: Amortized O(\log N).
 * Status: tested on https://codingcompetitions.withgoogle.com/codejam/round/0000000000c9607c/0000000000cad77d.
 */
struct UndoDSU {
	vi fa, siz;
	vector<pii> sta;

	UndoDSU(int n) : fa(n), siz(n, 1) {
		iota(all(fa), 0);
	}

	int getcomp(int x) {
		while (x != fa[x]) x = fa[x];
		return x;
	}

	bool merge(int x, int y) {
		int fx = getcomp(x), fy = getcomp(y);
		if (fx == fy) return 0;
		if (siz[fx] < siz[fy]) swap(fx, fy);
		sta.emplace_back(fx, fy);
		fa[fy] = fx;
		siz[fx] += siz[fy];
		return 1;
	}

	int top() { return sz(sta); }

	void undo(int top) {
		while (sz(sta) > top) {
			auto [x, y] = sta.back();
			fa[y] = y;
			siz[x] -= siz[y];
			sta.pop_back();
		}
	}
};