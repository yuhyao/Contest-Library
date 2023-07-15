/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Tarjan algorithm for directed graph $G = (V, E)$. 
 * Status: tested on http://ejudge.opencup.org/~ejudge/team.cgi?contest_id=2745 problem J. 
 */
auto tarjan(const vector<vi> &g) {
	int n = sz(g);
	vi id(n, -1), dfn(n, -1), low(n, -1), sta;
	int cnt = 0, scc = 0;

	auto dfs = [&](auto &dfs, int now) -> void {
		dfn[now] = low[now] = cnt++;
		sta.push_back(now);
		for (auto v: g[now]) {
			if (dfn[v] == -1) {
				dfs(dfs, v);
				low[now] = min(low[now], low[v]);
			} else if (id[v] == -1) low[now] = min(low[now], dfn[v]);
		}
		if (low[now] == dfn[now]) {
			while (1) {
				int z = sta.back();
				sta.pop_back();
				id[z] = scc;
				if (z == now) break;
			}
			scc++;
		}
	};
	rep(i, 0, n - 1) if (dfn[i] == -1) dfs(dfs, i);
	return make_tuple(scc, id);
}