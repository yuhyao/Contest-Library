/**
 * Author: Yuhao Yao
 * Date: 22-12-03
 * Description: Given a weighted undirected graph $G = (V, E)$, compute the minimum spanning tree using Prim's algorithm and returns the indices of edges chosen for the MST.
 *  Edge weights should be strictly smaller than $numerical\_limits<T>::max()$.
 * Time: O(|V|^2).
 * Status: tested on https://www.luogu.com.cn/problem/P5540, need more tests.
 */
template<class T>
vi Prim(int n, const vector<tuple<int, int, T>> &es) {
	const T inf = numeric_limits<T>::max();
	vector<vi> g(n);
	rep(i, 0, sz(es) - 1) {
		auto [x, y, w] = es[i];
		g[x].push_back(i);
		g[y].push_back(i);
	}
	vector<pair<T, int>> dis(n, {inf, -1});
	vi vis(n, 0);
	auto push = [&](int now) {
		vis[now] = 1;
		dis[now] = {inf, -1};
		for (auto ind: g[now]) {
			auto [x, y, w] = es[ind];
			int v = now ^ x ^ y;
			if (vis[v] == 0) {
				dis[v] = min(dis[v], {w, ind});
			}
		}
	};
	push(0);
	vi res;
	rep(i, 1, n - 1) {
		int j = min_element(all(dis)) - dis.begin();
		res.push_back(dis[j].second);
		push(j);
	}
	return res;
}