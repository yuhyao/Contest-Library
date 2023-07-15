/**
 * Author: Yuhao Yao
 * Date: 23-03-29
 * Description: Number Theoretic Transform. 
 *  class $T$ should have static function $getMod()$ to provide the $mod$. We usually just use $modnum$ as the template parameter.
 *  To keep the code short we just set the primitive root as $3$. However, it might be wrong when $mod \ne 998244353$. Here are some commonly used $mod$s and the corresponding primitive root.\\
 *  $g \to  mod~(\max \log(n))$:\\
 *  3 $\to$ 104857601 (22), 167772161 (25), 469762049 (26), 998244353 (23), 1004535809 (21);\\
 *  10 $\to$ 786433 (18);\\
 *  31 $\to$ 2013265921 (27).
 * Usage: const int mod = 998244353;
 *  using Mint = Z<mod>; // Z is modnum struct.
 *  ...
 *  FFT<Mint> ntt(3); // use 3 as primitive root.
 *  vector<Mint> as = ntt.conv(vector<Mint>{1, 2, 3}, vector<Mint>{2, 3, 4});
 * Time: O(N \log N).
 * Status: tested on https://ac.nowcoder.com/acm/contest/33186/H, https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence.
 */
template<class mint>
struct FFT {
	static void dft(vector<mint> &as, int is_inv) { // is_inv == 1 -> idft.
		static int mod = mint::getMod();
		static mint root = 0;
		if (root == 0) {
			root = 2;
			while (root.pow((mod - 1) / 2) == 1) root += 1; // it is not necessarily a primitive root but lowbit(mod - 1) divides its order.
		}
		
		int n = sz(as);
		assert(__builtin_popcount(n) == 1);
		static vi r;
		if (sz(r) != n) {
			r.resize(n);
			rep(i, 1, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (__builtin_ctz(n) - 1));
		}
		
		rep(i, 1, n - 1) if (r[i] > i) swap(as[i], as[r[i]]);
		for(int step = 1; step < n; step <<= 1) {
			mint zeta = root.pow((mod - 1) / (step << 1));
			if (is_inv) zeta = mint{1} / zeta;
			vector<mint> ws(step);
			ws[0] = 1;
			rep(i, 1, step - 1) ws[i] = ws[i - 1] * zeta;
			for (int i = 0; i < n; i += step << 1) {
				rep(j, 0, step - 1) {
					auto x = as[i + j], y = as[i + j + step] * ws[j];
					as[i + j] = x + y;
					as[i + j + step] = x - y;
				}
			}
		}
		
		if (is_inv == 1) {
			auto inv = mint{1} / n;
			for (auto &x: as) x *= inv;
		}
	}
	
	static vector<mint> conv(const vector<mint> &as, const vector<mint> &bs) {
		if (min(sz(as), sz(bs)) <= 128) {
			vector<ll> cs(sz(as) + sz(bs) - 1);
			rep(i, 0, sz(as) - 1) rep(j, 0, sz(bs) - 1) cs[i + j] += (int) (as[i] * bs[j]);
			return {all(cs)};
		} else {
	 		int n = sz(as) + sz(bs) - 1, n2 = 1 << __lg(n * 2 - 1);
			auto xs = as, ys = bs;
	 		xs.resize(n2, 0);
	 		ys.resize(n2, 0);
	 		dft(xs, 0); 
			if (as == bs) ys = xs;
			else dft(ys, 0);
	 		rep(i, 0, n2 - 1) xs[i] *= ys[i];
	 		dft(xs, 1);
	 		xs.resize(n);
	 		return xs;
		}
	}
};