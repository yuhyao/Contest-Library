/**
 * Author: Yuhao Yao
 * Date: 23-10-01
 * Description: Capacity Scaling algorithm for flow graph $G = (V, E)$.
 * Time: O(|E|^2 \log{U}) where $U$ is the maximum capacoty over all edges.
 * Status: tested on https://codeforces.com/contest/1082/problem/G. Need more tests.
 *  get_dir_flow() and get_undir_flow() are not tested yet.
 */
template<class flow_t = int>
struct CapacityScaling {
	int n; /// start-hash
	struct E { int to; flow_t a; }; // Endpoint & Admissible flow.
	vector<E> es;
	vector<vi> g;

	CapacityScaling(int n) : n(n), g(n) {}

	void add_edge(int u, int v, flow_t c, bool dir = 1) {
		g[u].push_back(sz(es)); es.push_back({v, c});
		g[v].push_back(sz(es)); es.push_back({u, dir ? 0 : c});
	}

	flow_t max_flow(int src, int sink) {
		flow_t U = 0;
		for (auto [v, a] : es) U = max(U, a);

		vector<bool> vis;
		flow_t ans = 0;
		for (flow_t base = U; base; base >>= 1) {
			while (1) {
				auto dfs = [&](auto &dfs, int now) -> flow_t {
					if (now == sink) return base;
					vis[now] = true;
					for (auto i : g[now]) {
						auto [v, c] = es[i];
						if (!vis[v] && c >= base) {
							flow_t x = dfs(dfs, v);
							if (x == base) {
								es[i].a -= x;
								es[i ^ 1].a += x;
								return x;
							}
						}
					}
					return 0;
				};
				vis.assign(n, false);
				
				auto res = dfs(dfs, src);
				ans += res;
				if (res == 0) break;
			}
		}
		return ans;
	} /// end-hash

	// Gives flow on edge assuming it is directed/undirected. Undirected flow is signed.
	flow_t get_dir_flow(int i) { return es[i * 2 + 1].a; }
	flow_t get_undir_flow(int i) { return (es[i * 2 + 1].a - es[i * 2].a) / 2; }
};