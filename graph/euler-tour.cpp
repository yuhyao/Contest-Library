/**
 * Author: Yuhao Yao
 * Date: 24-01-08
 * Description: For an edge set $E$ such that each vertex has an even degree, compute Euler tour for each connected component.
 * Time: $O(|V| + |E|)$.
 * Status: tested on https://codeforces.com/problemset/problem/325/E, https://ac.nowcoder.com/acm/contest/4010/H.
 */
struct EulerTour {
	int n; 
	vector<vi> tours;
	vi ori;

	EulerTour(int n, const vector<pii> &es, int dir = 0): n(n), ori(sz(es)) {
		vector<vi> g(n);
		int m = 0;
		for (auto [x, y]: es) {
			g[x].push_back(m);
			if (!dir) g[y].push_back(m);
			m++;
		}

		vi path, cur(n);
		auto dfs = [&](auto dfs, int now) -> void {
			for (int &i = cur[now]; i < sz(g[now]); ) {
				int ind = g[now][i++];
				if (ori[ind] != 0) continue;
				auto [x, y] = es[ind];
				ori[ind] = now == x ? 1 : -1;
				int v = now ^ x ^ y;
				dfs(dfs, v);
				path.push_back(ind);
			}
		};

		rep(i, 0, n - 1) {
			path.clear();
			dfs(dfs, i);
			if (sz(path)) {
				reverse(all(path));
				tours.push_back(path);
			}
		}
	}

	vector<vi> get_tours() { return tours; }

	vi get_orient() { return ori; }
};