/**
 * Author: Yuhao Yao
 * Date: 24-01-08
 * Description: Disjoint set union. $merge(x, y)$ merges components which $x$ and $y$ are in respectively and returns $1$ if $x$ and $y$ are in different components.
 * Time: amortized O(\alpha(M, N)) where $M$ is the number of operations. Almost constant in competitive programming.
 */
struct DSU {
	vi fa, siz;

	DSU(int n): fa(n), siz(n, 1) { iota(all(fa), 0); }

	int get_comp(int x) { 
		return fa[x] == x ? x : fa[x] = get_comp(fa[x]);
	}

	bool merge(int x, int y) {
		int fx = get_comp(x), fy = get_comp(y);
		if (fx == fy) return 0;
		if (siz[fx] < siz[fy]) swap(fx, fy);
		fa[fy] = fx;
		siz[fx] += siz[fy];
		return 1;
	}
};
