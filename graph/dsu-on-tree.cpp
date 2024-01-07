/**
 * Author: Yuhao Yao
 * Date: 23-03-03
 * Description: DSU on tree.
 * Time: O(N \log N)
*/
void DsuOnTree(const vector<vi> &g, function<void(int)> add, function<void(int)> remove, function<void(int)> solve, int rt = 0) {
	int n = sz(g);
	vi siz(n);
	int dfn = 0;
	auto calsz = [&](auto &dfs, int now, int fa) -> void {
		siz[now] = 1;
		for (auto v: g[now]) if (v != fa) {
			dfs(dfs, v, now);
			siz[now] += siz[v];
		}
	};
	calsz(calsz, rt, -1);

	vi tin(n), tout(n), ids(n);
	auto dfs = [&](auto &dfs, int now, int fa, bool keep) -> void {
		tin[now] = dfn;
		ids[dfn++] = now;
		
		int mx = 0, hv = -1;
		for (auto v : g[now]) if (v != fa && mx < siz[v]) { mx = siz[v]; hv = v; }
		for (auto v : g[now]) if (v != fa && v != hv) dfs(dfs, v, now, false);
		if (hv != -1) dfs(dfs, hv, now, true);
		tout[now] = dfn - 1;

		rep(ind, tin[now], (hv == -1 ? tout[now] : tin[hv] - 1)) add(ids[ind]);

		solve(now);

		if (keep == false) {
			rep(ind, tin[now], tout[now]) remove(ids[ind]);
		}
	};
	dfs(dfs, rt, -1, 0);
}
