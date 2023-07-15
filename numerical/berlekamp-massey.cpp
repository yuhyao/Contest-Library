/**
 * Author: Yuhao Yao
 * Date: 23-05-10
 * Description: Berlekamp-Massey Algorithm finds the shortest linear recurrence of sequence $a$. Given $a_0, \ldots, a_{n - 1}$, it finds shortest sequence $c_0, \ldots, c_{m - 1}$ such that $c_0 = 1$ and $\sum_{j = 0}^{m - 1} c_j \cdot a_{i - j} = 0$ for all $i \ge m - 1$.
 * Usage: BerlekampMMassey bm(vector<mint>{1, 2, 4});
   vector<mint> cs = bm.getRec();
   mint val = bm.kthTerm(1ll << 60);
 * TIme: $O(nm)$ for finding sequence $c$ where $m$ is the length of $c$; $O(m^2 \log k)$ for getting the $k$-th term.
 * Status: tested on https://judge.yosupo.jp/problem/find_linear_recurrence, https://qoj.ac/problem/2574.
 */
template<class T>
class BerlekampMassey {
	vector<T> as, cs;
public:
	BerlekampMassey(const vector<T> &as): as(as), cs{1} {
		vector<T> old_cs{1};
		int old_i = -1;
		T old_delta = 1;
		rep(i, 0, sz(as) - 1) {
			T delta = 0;
			rep(j, 0, sz(cs) - 1) delta += cs[j] * as[i - j];
			if (delta == 0) continue;

			T mult = delta / old_delta;
			vector<T> ncs = cs;
			ncs.resize(max(sz(cs), i - old_i + sz(old_cs)));
			rep(j, 0, sz(old_cs) - 1) ncs[j + i - old_i] -= old_cs[j] * mult;

			if (i - sz(cs) > old_i - sz(old_cs)) {
				old_i = i; 
				old_delta = delta;
				swap(old_cs, cs);
			}
			swap(cs, ncs);
		}
	}
	vector<T> getRec() { return cs; }
	
	T kthTerm(ll k) {
		auto polymul = [&](const vector<T> &as, const vector<T> &bs) {
			vector<T> res(sz(as) + sz(bs) - 1);
			rep(i, 0, sz(as) - 1) rep(j, 0, sz(bs) - 1) res[i + j] += as[i] * bs[j];
			if (sz(res) < sz(cs)) return res;
			
			revrep(i, sz(cs) - 1, sz(res) - 1) {
				revrep(j, 0, sz(cs) - 1) res[i - j] -= cs[j] * res[i];
			}
			res.resize(sz(cs) - 1);
			return res;
		};

		vector<T> cur{1}, mult{0, 1};
		for (; k > 0; k >>= 1) {
			if (k & 1) cur = move(polymul(cur, mult));
			mult = move(polymul(mult, mult));
		}
		T res = 0;
		rep(i, 0, sz(cur) - 1) res += cur[i] * as[i];
		return res;
	}
};