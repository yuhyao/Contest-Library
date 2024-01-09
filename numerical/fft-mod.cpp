/**
 * Author: Yuhao Yao
 * Date: 23-03-23
 * Description: Convolution of integers wrt arbitrary $mod \le 2^{31} - 1$. $T$ can be \textbf{double} or \textbf{long double}.
 * Usage: FFTMod<Mint, double> fft;
 *  vector<Mint> cs = fft.conv(vector<Mint>{1, 2, 3}, vector<Mint>{3, 4, 5});
 * Time: O(N \log N).
 * Status: tested on https://www.luogu.com.cn/problem/P4245, https://judge.yosupo.jp/problem/convolution_mod_1000000007.
 */
template<class mint, class FFT = FFT<double>>
class FFTMod: FFT {
	using typename FFT::cp;
	using FFT::dft;
public:
	static vector<mint> conv(const vector<mint> &as, const vector<mint> &bs) {
		if (min(sz(as), sz(bs)) <= 128) {
			vector<mint> cs(sz(as) + sz(bs) - 1);
			rep(i, 0, sz(as) - 1) rep(j, 0, sz(bs) - 1) cs[i + j] += as[i] * bs[j];
			return cs;
		} else {
			unsigned mod = mint::get_mod();
			int M = sqrt(mod) + 0.5;
			int n = sz(as) + sz(bs) - 1, n2 = 1 << __lg(n * 2 - 1);
			vector<cp> hs0(n2, 0), ls0(n2, 0), hs1(n2, 0), ls1(n2, 0);
			rep(i, 0, sz(as) - 1) hs0[i] = (int) as[i] / M, ls0[i] = (int) as[i] % M;
			rep(i, 0, sz(bs) - 1) hs1[i] = (int) bs[i] / M, ls1[i] = (int) bs[i] % M;
			
			dft(hs0, 0); dft(ls0, 0); dft(hs1, 0); dft(ls1, 0);
			vector<mint> res(n);

			auto work = [&](vector<cp> &as, vector<cp> &bs, int w) {
				vector<cp> tmp(n2);
				rep(i, 0, n2 - 1) tmp[i] = as[i] * bs[i];
				dft(tmp, 1);
				rep(i, 0, n - 1) res[i] += (ll)(tmp[i].real() + 0.5) % mod * w;
			};
			work(hs0, hs1, 1ll * M * M % mod);
			work(ls0, ls1, 1);
			work(hs0, ls1, M);
			work(ls0, hs1, M);
			return res;
		}
	}
};