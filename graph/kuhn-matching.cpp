/**
 * Author: Yuhao Yao
 * Date: 22-12-03
 * Description: Kuhn Matching algorithm for \textbf{bipartite} graph $G = (L \cup R, E)$. Edges $E$ should be described as pairs such that pair $(x, y)$ means that there is an edge between the $x$-th vertex in $L$ and the $y$-th vertex in $R$. Returns a vector $lm$, where $lm[i]$ denotes the vertex in $R$ matched to the $i$-th vertex in $R$.
 * Time: O((|L| + |R|) |E|).
 * Status: tested on https://www.luogu.com.cn/problem/P2764, https://www.luogu.com.cn/problem/P3386.
 */
vi Kuhn(int n, int m, const vector<pii> &es) {
	vector<vi> g(n);
	for (auto [x, y] : es) g[x].push_back(y);
	vi rm(m, -1);
	rep(i, 0, n - 1) {
		vi vis(m);
		auto dfs = [&](auto &dfs, int x) -> int {
			for (auto y : g[x]) if (vis[y] == 0) {
				vis[y] = 1;
				if (rm[y] == -1 || dfs(dfs, rm[y])) {
					rm[y] = x;
					return 1;
				}
			}
			return 0;
		};
		dfs(dfs, i);
	}
	vi lm(n, -1);
	rep(i, 0, m - 1) if (rm[i] != -1) lm[rm[i]] = i;
	return lm;
}
