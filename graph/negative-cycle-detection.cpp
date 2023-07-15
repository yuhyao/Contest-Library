/**
 * Author: Yuhao Yao
 * Date: 22-070-24
 * Description: Use Bellman-Ford Algprithm to detect negative cycles. Return true iff there exists a negative cycle.
 * Time: O(|V||E|).
 * Status: tested on https://codeforces.com/gym/102394/problem/A.
 */

template<class T> struct Edge {
	int u, v; T w;
};

template<class T>
bool NegCycle(int n, const vector<Edge<T>> &es) {
	vector<T> dis(n, 0);
	rep(rd, 1, n - 1) for (auto [u, v, w]: es) {
		dis[v] = min(dis[v], dis[u] + w);
	}
	for (auto [u, v, w]: es) if (dis[v] > dis[u] + w) return 1;
	return 0;
}