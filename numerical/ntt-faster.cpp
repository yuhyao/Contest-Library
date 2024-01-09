/**
 * Author: Yuhao Yao
 * Date: 23-03-28
 * Description: Number Theoretic Transform. 
 *  class $T$ should have static function $get\_mod()$ to provide the $mod$. We usually just use $modnum$ as the template parameter.
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
		static int mod = mint::get_mod();
		static mint root = 0; 
		static vector<mint> ws(__builtin_ctz(mod - 1)), iws(ws);
		if (root == 0) {
			root = 2;
			while (root.pow((mod - 1) / 2) == 1) root += 1; // it is not necessarily a primitive root but lowbit(mod - 1) divides its order.
			rep(i, 0, sz(ws) - 2) { // ws.back() is just a place-holder.
				ws[i] = -root.pow((mod - 1) >> (i + 2));
				iws[i] = mint{1} / ws[i];
			}
		}

		int n = sz(as);
		assert(__builtin_popcount(n) == 1);
		if (is_inv == 0) {
			for (int step = n >> 1; step; step >>= 1) {
				mint w = 1;
				for (int off = 0, k = 0; off < n; off += step * 2) {
					rep(i, 0, step - 1) {
						auto x = as[off + i], y = as[off + i + step] * w;
						as[off + i] = x + y;
						as[off + i + step] = x - y;
					}
					w *= ws[__builtin_ctz(++k)];
				}
			}
		} else {
			for (int step = 1; step < n; step <<= 1) {
				mint w = 1;
				for (int off = 0, k = 0; off < n; off += step * 2) {
					rep(i, 0, step - 1) {
						auto x = as[off + i], y = as[off + i + step];
						as[off + i] = x + y;
						as[off + i + step] = (x - y) * w;
					}
					w *= iws[__builtin_ctz(++k)];
				}
			}
			auto inv = mint{1} / n;
			for (auto& x: as) x *= inv;
		}
	}

	static vector<mint> conv(const vector<mint> &as, const vector<mint> &bs) {
		if (min(sz(as), sz(bs)) <= 30) {
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