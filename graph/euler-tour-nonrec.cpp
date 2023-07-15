/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: For an edge set $E$ such that each vertex has an even degree, compute Euler tour for each connected component. $dir$ indicates edges are directed or not (undirected by default). For undirected graph, $ori[i]$ records the orientation of the $i$-th edge $es[i] = (x, y)$, where $ori[i] = 1$ means $x \to y$ and $ori[i] = -1$ means $y \to x$.
 *  Note that this is a non-recursive implementation, which avoids stack size issue on some OJ and also saves memory (roughly saves 2/3 of memory) due to that.
 * Time: $O(|V| + |E|)$.
 * Status: tested on https://acm.hdu.edu.cn/showproblem.php?pid=7261, https://ac.nowcoder.com/acm/contest/4010/H.
 */

struct EulerTour {
	int n;
	vector<vi> tours;
	vi ori;

	EulerTour(int n, const vector<pii> &es, int dir = 0): n(n), ori(sz(es)) {
		vector<vi> g(n);
		int m = sz(es);
		rep(i, 0, m - 1) {
			auto [x, y] = es[i];
			g[x].push_back(i);
			if (dir == 0) g[y].push_back(i);
		}

		vi path, cur(n);
		vector<pii> sta;
		auto solve = [&](int st) {
			sta.emplace_back(st, -1);
			while (sz(sta)) {
				auto [now, pre] = sta.back();
				int fin = 1;
				for (int &i = cur[now]; i < sz(g[now]); ) {
					auto ind = g[now][i++];
					if (ori[ind]) continue;
					auto [x, y] = es[ind];
					ori[ind] = x == now ? 1 : -1;
					int v = now ^ x ^ y;
					sta.emplace_back(v, ind);
					fin = 0;
					break;
				}
				if (fin) {
					if (pre != -1) path.push_back(pre);
					sta.pop_back();
				}
			}
		};

		rep(i, 0, n - 1) {
			path.clear();
			solve(i);
			if (sz(path)) {
				reverse(all(path));
				tours.push_back(path);
			}
		}
	}

	vector<vi> getTours() { return tours; }

	vi getOrient() { return ori; }
};
