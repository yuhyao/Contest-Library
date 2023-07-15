/**
 * Author: Yuhao Yao
 * Date: 23-03-28
 * Description: Basic polynomial struct. Usually we use $modnum$ as template parameter. $inv(k)$ gives the inverse of the polynomial $mod~ x^k$ (by default $k$ is the highest power plus one).
 * Status: 
 *  inv() tested on https://www.luogu.com.cn/problem/P4238, https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence.
 *  ln() tested on https://www.luogu.com.cn/problem/P4725.
 *  exp() tested on https://www.luogu.com.cn/problem/P4726, https://judge.yosupo.jp/problem/exp_of_formal_power_series.
 */
template<class T, class FFT = FFT<T>>
struct Poly : vector<T> {
	using poly = Poly;
	using vector<T>::vector;
	Poly(const vector<T> &vec) : vector<T>(vec) {}
	Poly(vector<T> &&vec) : vector<T>(vec) {}
	
	friend poly& operator +=(poly &as, const poly &bs) { /// start-hash
		if (sz(as) < sz(bs)) as.resize(sz(bs), 0);
		rep(i, 0, sz(bs) - 1) as[i] += bs[i];
		return as;
	} 
	friend poly operator +(const poly &as, const poly &bs) { auto cs = as; return cs += bs; }

	friend poly& operator -=(poly &as, const poly &bs) {
		if (sz(as) < sz(bs)) as.resize(sz(bs), 0);
		rep(i, 0, sz(bs) - 1) as[i] -= bs[i];
		return as;
	}
	friend poly operator -(const poly &as, const poly &bs) { auto cs = as; return cs -= bs; }

	friend poly& operator *=(poly &as, const poly &bs) {
		as = FFT::conv(as, bs);
		return as;
	}
	friend poly operator *(const poly &as, const poly &bs) { auto cs = as; return cs *= bs; }
	friend poly& operator *=(poly &as, const T &b) {
		for (auto &x : as) x *= b;
		return as;
	}
	friend poly operator *(const poly &as, const T &b) { auto cs = as; return cs *= b; }
	friend poly operator *(const T &a, const poly &bs) { auto cs = bs; return cs *= a; }
	/// end-hash
	poly modxk(int k) const {
		return poly(this->begin(), this->begin() + min(sz(*this), k));
	}
	poly derivative() const {
		assert(sz(*this) > 0);
		auto as = poly(this->begin() + 1, this->end());
		rep(i, 0, sz(as) - 1) as[i] *= i + 1;
		if (sz(as) == 0) as = poly{0};
		return as;
	}
	poly integral() const {
		poly as(sz(*this) + 1);
		rep(i, 1, sz(as) - 1) as[i] = (*this)[i - 1] / i;
		return as;
	}

	poly inv(int k = 0) const { /// start-hash
		const poly &as = *this;
		assert(sz(as) > 0);
		if (k == 0) k = sz(as);
		poly res{T{1} / as[0]};
		for (int m = 2; m < k * 2; m <<= 1) {
			res = res * 2 - (res * res * as.modxk(m)).modxk(m);
		}
		res.resize(k);
		return res;
	} /// end-hash
	poly ln(int k = 0) const {
		poly as = *this;
		if (k > 0) as.resize(k);
		assert(sz(as) > 0 && as[0] == T{1}); // be cautious when T is float or double.
		return (as.derivative() * as.inv()).modxk(sz(as) - 1).integral();
	}
	poly exp(int k = 0) const {
		const poly &as = *this;
		if (k == 0) k = sz(as);
		assert(k > 0 && (sz(as) == 0 || as[0] == T{0})); // be cautious when T is float or double.
		poly res{1};
		for (int m = 2; m < k * 2; m <<= 1) {
			res = res - (res * (res.ln(m) - as.modxk(m))).modxk(m);
		}
		res.resize(k);
		return res;
	}
};