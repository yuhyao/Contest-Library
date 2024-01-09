/**
 * Author: Yuhao Yao
 * Date: 23-04-24
 * Description: Binomial Coefficients $\binom(n, m)$ for $n \le N$. One can also calculate array $inv$ first by $inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod$ and then get $ifac$.
 * Time: O(N) for pre-calculate, O(1) for each query.
 * Status: tested on https://codeforces.com/contest/1821/problem/F.
 */
template<class T>
struct Binomial {
	int N;
	vector<T> fac, ifac;
	Binomial(int N) : N(N), fac(N + 1), ifac(N + 1) {
		fac[0] = 1;
		rep(i, 1, N) fac[i] = fac[i - 1] * i;
		ifac[N] = T{1} / fac[N];
		revrep(i, 1, N) ifac[i - 1] = ifac[i] * i;
	}
	T operator ()(int n, int m) {
		if (m < 0 || n < m) return 0;
		else return fac[n] * ifac[m] * ifac[n - m];
	}
};