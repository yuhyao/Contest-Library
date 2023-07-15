template<class F, class C, F F_MAX = numeric_limits<F>::max(), C C_MAX = numeric_limits<C>::max() / 4>
class PrimalDual {
    int n;
    struct E { int v; F cap; C w; };
    vector<E> e;
    vector<vi> g;
    vector<C> h;
public:
    PrimalDual(int n): n(n), g(n), h(n) {}

    void add(int u, int v, F c, C w) {
        g[u].push_back(sz(e)); e.push_back({v, c, w});
        g[v].push_back(sz(e)); e.push_back({u, 0, -w});
    }

    pair<C, F> mincostflow(int src, int sink, F mx_flow = F_MAX) {
        // Run Bellman-Ford first if necessary.
        h.assign(n, C_MAX);
        h[src] = 0;
        rep(rd, 1, n) rep(now, 0, n - 1) for (auto i: g[now]) {
            auto [v, c, w] = e[i];
            if (c > 0) h[v] = min(h[v], h[now] + w);
        }
        // Bellman-Ford stops here.

        C cost = 0; F flow = 0;
        while(mx_flow) {
            priority_queue<pair<C, int> > pq;
            vector<C> dis(n, C_MAX);
            dis[src] = 0; pq.push({0, src});
            
            vi mark(n, 0);
            while (sz(pq)) {
                auto [d, now] = pq.top(); pq.pop();
                // Using mark[] is safer than compare -d and dis[now] when the cost is float type.
                if (mark[now]) continue;
                mark[now] = 1;
                for (auto i: g[now]) {
                    auto [v, c, w] = e[i];
                    C off = dis[now] + w + h[now] - h[v];
                    if (c > 0 && dis[v] > off) dis[v] = off, pq.push({-dis[v], v});
                }
            }
            if (dis[sink] == C_MAX) break;
            
            vi cur(n, 0);
            vector<bool> vis(n, 0);
            function<F(int, F)> dfs = [&](int now, F flow) {
                if (now == sink) return flow;
                F res = 0;
                vis[now] = 1;
                for (int &id = cur[now]; id < sz(g[now]); id++) {
                    int i = g[now][id];
                    auto [v, c, w] = e[i];
                    if (vis[v] == 0 && c > 0 && dis[v] == dis[now] + w + h[now] - h[v]) {
                        F x = dfs(v, min(flow - res, c));
                        res += x;
                        e[i].cap -= x;
                        e[i ^ 1].cap += x;
                    }
                    if (res == flow) break;
                }
                vis[now] = 0;
                return res;
            };

            F aug = dfs(src, mx_flow);
            rep(i, 0, n - 1) if (dis[i] != C_MAX) h[i] += dis[i];
            mx_flow -= aug;
            cost += aug * h[sink];
        }
        return {cost, flow};
    }
    // Calculate distance on residual graph
    C cal_dis(int st, int ed) {
        priority_queue<pair<C, int> > pq;
        vector<C> dis(n, C_MAX); 
        dis[st] = 0; pq.push({0, st});
        vi mark(n, 0);
        while (sz(pq)) {
            auto [d, now] = pq.top(); pq.pop();
            if (mark[now]) continue; // again, using mark is safe when C = double.
            mark[now] = 1;
            for (auto i: g[now]) {
                auto [v, c, w] = e[i];
                C off = dis[now] + w + h[now] - h[v];
                if (c > 0 && dis[v] > off) dis[v] = off, pq.push({-dis[v], v});
            }
        }
        return dis[ed] + h[ed] - h[st];
    }
};