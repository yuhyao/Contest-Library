/**
 * Author: Yuhao Yao
 * Date: 23-04-07
 * Description: Segment tree (zkw style, small constant factor). Point apply and thus no lazy propogation.
 * Usage: Always define a InfoApply function for class $Info$ you use to tell segment tree how you apply modification.
 *  Combine is set as plus so if you just let T be numerical type then you have range sum in the info and as range query result. To have something different, say rangeMin, define a struct with constructer and + operation.
 * Time: O(\log N) per operation.
 * Status: tested on https://mirror.codeforces.com/gym/437416/problem/L.
 */
template<class Info>
struct Segtree {
	int n;
	vector<Info> info;

	Segtree(int n): n(n) {
		assert(n > 0);
		info.resize(n * 2);
	}
	Segtree(const vector<Info> &init): Segtree(sz(init)) {
		rep(i, 0, n - 1) info[n + i] = init[i];
		revrep(i, 0, n - 1) info[i] = info[i * 2] + info[i * 2 + 1];
	}

	template<class... T>
	void pointApply(int p, const T&... val) {
		InfoApply(info[n + p], val...);
		for (p = (n + p) >> 1; p; p >>= 1) {
			info[p] = info[p * 2] + info[p * 2 + 1];
		}
	}
	
	Info rangeAsk(int l, int r) {
		Info resl{}, resr{};
		for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
			if (l & 1) resl = resl + info[l++];
			if (r & 1) resr = info[--r] + resr;
		}
		return resl + resr;
	}
};