/**
 * Author: Yuhao Yao
 * Date: 23-05-01
 * Description: Undoable Disjoint Union Set for set ${0, ..., N - 1}$. 
 *  Use $top = top()$ to get a save point; use $undo(top)$ to go back to the save point.
 *  Note that Info should have a member function $join$ and a static variable $global$;
 * Usage: 
 *  UndoDSU dsu(n);
 *  ...
 *  int top = dsu.top(); // get a save point.
 *  ... // do merging and other calculating here.
 *  dsu.undo(top); // get back to the save point.
 * Time: Amortized O(\log N).
 * Status: tested on https://ac.nowcoder.com/acm/contest/33193/I.
 */
template<class Info>
struct UndoDSU {
	using T = decltype(Info::global);
	vi fa, siz;
	vector<Info> info;
	vector<tuple<int, int, Info, T>> sta;

	UndoDSU(const vector<Info> &init) : fa(sz(init)), siz(sz(init), 1), info(init) {
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
		sta.emplace_back(fx, fy, info[fx], Info::global);
		fa[fy] = fx;
		siz[fx] += siz[fy];
		info[fx].join(info[fy]);
		return 1;
	}

	int top() { return sz(sta); }

	void undo(int top) {
		while (sz(sta) > top) {
			const auto &[x, y, w, global] = sta.back();
			fa[y] = y;
			siz[x] -= siz[y];
			info[x] = w;
			Info::global = global;
			sta.pop_back();
		}
	}
};