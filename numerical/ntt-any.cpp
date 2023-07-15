/**
 * Author: Yuhao Yao
 * Date: 23-03-28
 * Description: Convolution of integers wrt arbitrary $mod \le 2^{31} - 1$.
 * Usage:
 *  static const int mod = 1e9 + 7;
 *  using mint = MInt<mod>;
 *  vector<mint> cs = FFTMod<mint, MInt, FFT>::conv(vector<mint>{1, 2, 3}, vector<mint>{3, 4, 5});
 * Time: O(N \log N).
 * Status: tested on https://www.luogu.com.cn/problem/P4245.
 */
template<class mint, template<const unsigned&> class MInt = MInt, template<class> class FFT = FFT>
struct FFTMod {
	static vector<mint> conv(const vector<mint>& as, const vector<mint>& bs) {
		if (as.empty() || bs.empty()) return {};
		int n = as.size(), m = bs.size();
		static const unsigned mod0 = 998244353, mod1 = 1300234241, mod2 = 1484783617;
		using mint0 = MInt<mod0>;
		using mint1 = MInt<mod1>;
		using mint2 = MInt<mod2>;
		vector<mint0> l0(n), r0(m);
		vector<mint1> l1(n), r1(m);
		vector<mint2> l2(n), r2(m);
		for (int i = 0; i < n; ++i) l0[i] = (int) as[i], l1[i] = (int) as[i], l2[i] = (int) as[i];
		for (int j = 0; j < m; ++j) r0[j] = (int) bs[j], r1[j] = (int) bs[j], r2[j] = (int) bs[j];
		l0 = FFT<mint0>::conv(l0, r0);
		l1 = FFT<mint1>::conv(l1, r1);
		l2 = FFT<mint2>::conv(l2, r2);
		vector<mint> res(n + m - 1);
		const mint1 im0 = 1 / mint1(mod0);
		const mint2 im1 = 1 / mint2(mod1), im0m1 = im1 / mod0;
		const mint m0 = mod0, m0m1 = m0 * mod1;
		for (int i = 0; i < n + m - 1; ++i) {
			int y0 = (int) l0[i];
			int y1 = (int) (im0 * (l1[i] - y0));
			int y2 = (int) (im0m1 * (l2[i] - y0) - im1 * y1);
			res[i] = y0 + m0 * y1 + m0m1 * y2;
		}
		return res;
	}
};