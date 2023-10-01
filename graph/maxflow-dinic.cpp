/**
 * Author: Yuhao Yao
 * Date: 23-10-01
 * Description: Dinic algorithm for flow graph $G = (V, E)$. You can also get a minimum $src-sink$ cut easily.
 * Time: O(|V|^2 |E|) for arbitrary networks. O(|E| \sqrt{|V|}) for bipartite/unit network. O(min{|V|^{2/3}, |E|^{1/2}} |E|) for networks with only unit capacities.
 * Status: tested on https://codeforces.com/contest/1082/problem/G, https://codeforces.com/gym/103861/problem/H. Seems to be fast enough now.
 *  get_dir_flow() and get_undir_flow() are not tested yet.
 */
template<class Cap = int>
struct Dinic {
	int n; /// start-hash
	struct E { int to; Cap a; }; // Endpoint & Admissible flow.
	vector<E> es;
	vector<vi> g;
	vi dis; // Put it here to get the minimum cut easily.

	Dinic(int n): n(n), g(n) {}

	void add_edge(int u, int v, Cap c, bool dir = 1) {
		g[u].push_back(sz(es)); es.push_back({v, c});
		g[v].push_back(sz(es)); es.push_back({u, dir ? 0 : c});
	}

	Cap max_flow(int src, int sink) {
		auto revbfs = [&]() {
			dis.assign(n, -1);
			dis[sink] = 0;
			vi que{sink};
			
			rep(ind, 0, sz(que) - 1) {
				int now = que[ind];
				for (auto i: g[now]) {
					int v = es[i].to;
					if (es[i ^ 1].a > 0 && dis[v] == -1) {
						dis[v] = dis[now] + 1;
						que.push_back(v);
						if (v == src) return 1;
					}
				}
			}
			return 0;
		};

		vi cur;
		auto dfs = [&](auto &dfs, int now, Cap flow) {
			if (now == sink) return flow;
			Cap res = 0;
			for (int &ind = cur[now]; ind < sz(g[now]); ind++) {
				int i = g[now][ind];
				auto [v, c] = es[i];
				if (c > 0 && dis[v] == dis[now] - 1) {
					Cap x = dfs(dfs, v, min(flow - res, c));
					res += x;
					es[i].a -= x;
					es[i ^ 1].a += x;
				}
				if (res == flow) break;
			}
			return res;
		};
		
		Cap ans = 0;
		while (revbfs()) {
			cur.assign(n, 0);
			ans += dfs(dfs, src, numeric_limits<Cap>::max());
		}
		return ans;
	} /// end-hash

	// Returns a min-cut containing source src.
	pair<Cap, vi> min_cut(int src, int sink) { /// start-hash
		Cap ans = max_flow(src, sink);
		vi res;
		rep(i, 0, n - 1) if (dis[i] == -1) res.push_back(i);
		return make_pair(ans, move(res));
	} /// end-hash

	// Gives flow on edge assuming it is directed/undirected. Undirected flow is signed.
	Cap get_dir_flow(int i) { return es[i * 2 + 1].a; }
	Cap get_undir_flow(int i) { return (es[i * 2 + 1].a - es[i * 2].a) / 2; }
};