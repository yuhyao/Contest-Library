/**
 * Author: Yuhao Yao
 * Date: 23-01-27
 * Description: Successive Shortest Path for flow graph $G = (V, E)$. 
 *  Run $mincostflow(src, sink)$ for some $src$ and $sink$ to get the minimum cost and the maximum flow. For negative costs, Bellman-Ford is necessary.
 * Time: O(|F| |E|\log{|E|}) for non-negative costs, where $|F|$ is the size of maximum flow. O(|V| |E| + |F| |E|\log{|E|}) for arbitrary costs.
 * Status: tested on https://qoj.ac/contest/503/problem/1269, https://codingcompetitions.withgoogle.com/codejam/round/0000000000436142/0000000000813e1a, https://codeforces.com/gym/103371/problem/L, https://codeforces.com/gym/102759/problem/F.
 */
template<class flow_t, class cost_t>
struct SuccessiveShortestPath {
	int n;
	struct E { int to; flow_t a; cost_t w; };
	vector<E> es;
	vector<vi> g;
	vector<cost_t> h;
	bool neg_cost;

	SuccessiveShortestPath(int n): n(n), g(n), h(n), neg_cost(false) {}

	void add_edge(int u, int v, flow_t c, cost_t w) {
		g[u].push_back(sz(es)); es.push_back({v, c, w});
		g[v].push_back(sz(es)); es.push_back({u, 0, -w});
		if (w < 0) neg_cost = true;
	}

	pair<cost_t, flow_t> min_costflow(int src, int sink, flow_t mx_flow = numeric_limits<flow_t>::max()) {
		const cost_t INF = numeric_limits<cost_t>::max() / 4;
		if (neg_cost) { // Run Bellman-Ford when there exists negative cost.
			h.assign(n, INF);
			h[src] = 0;
			rep(rd, 1, n) rep(now, 0, n - 1) for (auto i: g[now]) {
				auto [v, c, w] = es[i];
				if (c > 0) h[v] = min(h[v], h[now] + w);
			}
		}

		cost_t cost = 0;
		flow_t flow = 0;
		while (mx_flow) {
			priority_queue<pair<cost_t, int>> pq;
			vector<cost_t> dis(n, INF);
			dis[src] = 0; pq.emplace(0, src);
			
			vi pre(n, -1), mark(n, 0);
			while (sz(pq)) {
				auto [d, now] = pq.top(); pq.pop();
				// Using mark[] is safer than compare -d and dis[now] when the cost_t = double.
				if (mark[now]) continue;
				mark[now] = 1;
				for (auto i : g[now]) {
					auto [v, c, w] = es[i];
					auto offer = dis[now] + w + h[now] - h[v];
					if (c > 0 && dis[v] > offer) {
						dis[v] = offer;
						pq.emplace(-dis[v], v);
						pre[v] = i;
					}
				}
			}
			if (pre[sink] == -1) break;
			
			rep(i, 0, n - 1) if (dis[i] != INF) h[i] += dis[i];
			auto aug = mx_flow;
			for (int i = pre[sink]; ~i; i = pre[es[i ^ 1].to]) aug = min(aug, es[i].a);
			for (int i = pre[sink]; ~i; i = pre[es[i ^ 1].to]) es[i].a -= aug, es[i ^ 1].a += aug;
			mx_flow -= aug;
			flow += aug;
			cost += aug * h[sink];
		}
		return {cost, flow};
	}
};