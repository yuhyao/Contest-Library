/**
 * Author: Yuhao Yao
 * Date: 23-10-03
 * Description: Highest label preflow push algorithm for flow graph $G = (V, E)$.
 * Time: O(|V|^2 \sqrt{|E|}}).
 * Status: tested on https://codeforces.com/contest/1082/problem/G. Need more tests.
 *  get_dir_flow() and get_undir_flow() are not tested yet.
 */
template<class flow_t = int>
struct HLPP {
	int n; /// start-hash
	struct E { int to; flow_t a; }; // Endpoint & Admissible flow.
	vector<E> es;
	vector<vi> g;

	HLPP(int n) : n(n), g(n) {}

	void add_edge(int u, int v, flow_t c, bool dir = 1) {
		g[u].push_back(sz(es)); es.push_back({v, c});
		g[v].push_back(sz(es)); es.push_back({u, dir ? 0 : c});
	}

	flow_t max_flow(int src, int sink) {
		const int inf = 0x3f3f3f3f;
		vi hs(n, inf);
		vector<flow_t> xs(n);
		vector<vi> bins(n);
		int level = 0;

		auto push = [&](int now) {
			bool init = now == src;
			for (auto i : g[now]) {
				auto [v, c] = es[i];
				if (c == 0 || (init == false && hs[now] != hs[v] + 1) || hs[v] == inf) continue;
				int k = init ? c : min(c, xs[now]);
				if (v != src && v != sink && xs[v] == 0) {
					bins[hs[v]].push_back(v);
					level = max(level, hs[v]);
				}
				xs[now] -= k, xs[v] += k;
				es[i].a -= k, es[i ^ 1].a += k;
				if (xs[now] == 0) return 0;
			}
			return 1;
		};

		vi que{sink};
		hs[sink] = 0;
		rep(ind, 0, sz(que) - 1) {
			int now = que[ind];
			for (auto i : g[now]) {
				int v = es[i].to;
				if (es[i ^ 1].a > 0 && hs[v] > hs[now] + 1) {
					hs[v] = hs[now] + 1;
					que.push_back(v);
				}
			}
		}
		if (hs[src] == inf) return 0;

		vi cnt(n);
		hs[src] = n;
		rep(i, 0, n - 1) if (hs[i] < n) cnt[hs[i]]++;
		push(src);
		while (1) {
			while (level >= 0 && sz(bins[level]) == 0) level--;
			if (level == -1) break;
			int now = bins[level].back();
			bins[level].pop_back();
			if (push(now)) {
				int &h = hs[now];
				if (--cnt[h] == 0) {
					rep(v, 0, n - 1) {
						if (v != src && hs[v] > h && hs[v] <= n)
							hs[v] = n + 1;
					}
				}
				h = inf;
				for (auto i : g[now]) {
					auto [v, c] = es[i];
					if (c > 0) h = min(h, hs[v] + 1);
				}
				if (h < n) {
					bins[h].push_back(now);
					level = max(level, h);
					cnt[h]++;
				}
			}
		}
		return xs[sink];
	} /// end-hash

	// Gives flow on edge assuming it is directed/undirected. Undirected flow is signed.
	flow_t get_dir_flow(int i) { return es[i * 2 + 1].a; }
	flow_t get_undir_flow(int i) { return (es[i * 2 + 1].a - es[i * 2].a) / 2; }
};