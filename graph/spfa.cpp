/**
 * Author: Yuhao Yao
 * Date: 23-03-26
 * Description: Shortest Path Faster Algorithm.
 * Time: O(|V||E|) in worst case.
 * Status: tested on https://www.luogu.com.cn/problem/P3371.
 */
template<class T>
vector<T> spfa(const vector<vector<pair<int, T>>> &g, int src) {
	int n = sz(g);
	
	deque<int> que{src};
	vector<T> dis(n, numeric_limits<T>::max()); dis[src] = 0;
	vi in(n, 0); in[src] = 1;
	
	while (sz(que)) {
		int now = que[0]; que.pop_front();
		in[now] = 0;
		for (auto [v, w]: g[now]) if (dis[v] > dis[now] + w) {
			dis[v] = dis[now] + w;
			if (in[v] == 0) {
				in[v] = 1;
				if (sz(que) && dis[v] < dis[que[0]]) que.push_front(v);
				else que.push_back(v);
			}
		}
	}
	return dis;
}