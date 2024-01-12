/**
 * Author: Yuhao Yao
 * Date: 23-03-23
 * Description: Fast Fourier Transform. $T$ can be \textbf{double} or \textbf{long double}.
 * Usage: FFT<double> fft;
 *  vector<double> cs = fft.conv(vector<double>{1, 2, 3}, vector<double>{3, 4, 5});
 *  vector<int> ds = fft.conv(vector<int>{1, 2, 3}, vector<int>{3, 4, 5});
 * Time: O(N \log N).
 * Status: tested on https://judge.yosupo.jp/problem/convolution_mod_1000000007.
 */
template<class T>
struct FFT {
	using cp = complex<T>;

	static void dft(vector<cp> &as, int is_inv) { // is_inv == 1 -> idft.
		const T pi = acos(T{-1});
		
		int n = sz(as);
		assert(__builtin_popcount(n) == 1);
		static vi r;
		if (sz(r) != n) {
			r.resize(n);
			rep(i, 1, n - 1) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (__builtin_ctz(n) - 1));
		}

		rep(i, 1, n - 1) if (r[i] > i) swap(as[i], as[r[i]]);
		for (int step = 1; step < n; step <<= 1) {
			vector<cp> ws(step);
			rep(j, 0, step - 1) { // this has higher precision, compared to using the power of zeta.
				T theta = pi * j / step;
				if (is_inv) theta = -theta;
				ws[j] = cp{cos(theta), sin(theta)};
			}
			for (int i = 0; i < n; i += step << 1) {
				rep(j, 0, step - 1) {
					auto tmp = ws[j] * as[i + j + step];
					as[i + j + step] = as[i + j] - tmp;
					as[i + j] += tmp;
				}
			}
		}
		if (is_inv) {
			for (auto &x: as) x /= n;
		}
	}

	template<class Z>
	static vector<Z> conv(const vector<Z> &as, const vector<Z> &bs) {
		if (min(sz(as), sz(bs)) <= 128) {
			vector<T> cs(sz(as) + sz(bs) - 1);
			rep(i, 0, sz(as) - 1) rep(j, 0, sz(bs) - 1) cs[i + j] += as[i] * bs[j];
			return cs;
		} else {
			int n = sz(as) + sz(bs) - 1, n2 = 1 << __lg(n * 2 - 1);
			vector<cp> xs(n2, 0), ys(n2, 0);
			rep(i, 0, sz(as) - 1) xs[i] = as[i];
			rep(i, 0, sz(bs) - 1) ys[i] = bs[i];
			
			dft(xs, 0); 
			if (as == bs) ys = xs;
			else dft(ys, 0);
			rep(i, 0, n2 - 1) xs[i] *= ys[i];
			dft(xs, 1);
			vector<Z> res(n);
			T eps = T{0.5} * (static_cast<Z>(1e-9) == 0);
			rep(i, 0, n - 1) res[i] = xs[i].real + eps;
			return res;
		}
	}
};
