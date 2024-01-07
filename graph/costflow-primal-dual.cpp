/**
 * Author: Yuhao Yao
 * Date: 23-10-04
 * Description: Successive Shortest Path for flow graph $G = (V, E)$.
 * Usage: Always run $mincostflow(src, sink)$ for some $src$ and $sink$ to get the minimum cost and the maximum flow.
 * Time: Unknown.
 * Status: tested on https://codeforces.com/gym/102759/problem/F.
 */
template<class flow_t, class cost_t>
class PrimalDual {
	int n;
	struct E { int to; flow_t a; cost_t w; };
	vector<E> es;
	vector<vi> g;
	vector<cost_t> hs;
	bool neg_cost;
public:
	PrimalDual(int n): n(n), g(n), hs(n), neg_cost(false) {}

	void add(int u, int v, flow_t c, cost_t w) {
		g[u].push_back(sz(es)); es.push_back({v, c, w});
		g[v].push_back(sz(es)); es.push_back({u, 0, -w});
		neg_cost |= w < 0;
	}

	pair<cost_t, flow_t> mincostflow(int src, int sink, flow_t feed = numeric_limits<flow_t>::max()) {
		const cost_t INF = numeric_limits<cost_t>::max() / 4;
		if (neg_cost) {
			hs.assign(n, INF);
			hs[src] = 0;
			rep(rd, 1, n) rep(now, 0, n - 1) for (auto i : g[now]) {
				auto [v, c, w] = es[i];
				if (c > 0) hs[v] = min(hs[v], hs[now] + w);
			}
		}

		cost_t cost = 0;
		flow_t flow = 0;
		while (feed) {
			priority_queue<pair<cost_t, int>> pq;
			vector<cost_t> dis(n, INF);
			dis[src] = 0; pq.emplace(0, src);
			
			vector<bool> mark(n, false);
			while (sz(pq)) {
				auto [d, now] = pq.top(); pq.pop();
				// Using mark[] is safer than compare -d and dis[now] when the cost is float type.
				if (mark[now]) continue;
				mark[now] = true;
				for (auto i : g[now]) {
					auto [v, c, w] = es[i];
					cost_t offer = dis[now] + w + hs[now] - hs[v];
					if (c > 0 && dis[v] > offer) {
						dis[v] = offer;
						pq.emplace(-dis[v], v);
					}
				}
			}
			if (dis[sink] == INF) break;
			
			vi cur(n, 0), vis(n, 0);
			auto dfs = [&](auto &dfs, int now, flow_t flow) {
				if (now == sink) return flow;
				flow_t res = 0;
				vis[now] = 1;
				for (int &id = cur[now]; id < sz(g[now]); id++) {
					int i = g[now][id];
					auto [v, c, w] = es[i];
					if (vis[v] == 0 && c > 0 && dis[v] == dis[now] + w + hs[now] - hs[v]) {
						flow_t x = dfs(dfs, v, min(flow - res, c));
						res += x;
						es[i].a -= x;
						es[i ^ 1].a += x;
					}
					if (res == flow) break;
				}
				vis[now] = 0;
				return res;
			};

			flow_t aug = dfs(dfs, src, feed);
			rep(i, 0, n - 1) if (dis[i] != INF) hs[i] += dis[i];
			feed -= aug;
			cost += aug * hs[sink];
		}
		return {cost, flow};
	}
	// Calculate distance on residual graph
	cost_t cal_dis(int st, int ed) {
		const cost_t INF = numeric_limits<cost_t>::max() / 4;
		priority_queue<pair<cost_t, int>> pq;
		vector<cost_t> dis(n, INF); 
		dis[st] = 0; pq.emplace(0, st);
		vector<bool> mark(n, false);
		while (sz(pq)) {
			auto [d, now] = pq.top(); pq.pop();
			if (mark[now]) continue; // again, using mark is safe when cost_t = double.
			mark[now] = true;
			for (auto i: g[now]) {
				auto [v, c, w] = es[i];
				auto off = dis[now] + w + hs[now] - hs[v];
				if (c > 0 && dis[v] > off) {
					dis[v] = off;
					pq.emplace(-dis[v], v);
				}
			}
		}
		return dis[ed] + hs[ed] - hs[st];
	}
};