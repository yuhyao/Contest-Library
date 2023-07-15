/**
 * Author: Yuhao Yao
 * Date: 23-03-26
 * Description: Dijkstra Algorithm.
 * Time: O(|E| \log{|V|}).
 * Status: tested on https://www.luogu.com.cn/problem/P4779.
 */
template<class T>
vector<T> dijkstra(const vector<vector<pair<int, T>>> &g, int src) {
	int n = sz(g);
	
	priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
	pq.emplace(0, src);
	vector<T> dis(n, numeric_limits<T>::max()); dis[src] = 0;
	vi mark(n);
	
	while (sz(pq)) {
		auto [_, now] = pq.top(); pq.pop();
		if (mark[now]) continue;
		mark[now] = 1;
		for (auto [v, w]: g[now]) if (dis[v] > dis[now] + w) {
			dis[v] = dis[now] + w;
			pq.emplace(dis[v], v);
		}
	}
	return dis;
}