/**
 * Author: Yuhao Yao
 * Date: 23-05-10
 * Description: historical sum with apply = set. A node $Mat(t, val)$ corresponds to setting the value to $val$ from time $t$ (including $t$). Use $getVal(t)$ to get historical sum up to time $t$ (including $t$).
 * Status: tested on https://codeforces.com/contest/1824/problem/D.
 */
template<class T> /// start-hash
struct Mat {
	T v10, v11, v20, v21;
	Mat() { v10 = v20 = v21 = 0; v11 = 1; }
	Mat(int t, T val) {
		v10 = t - 1;
		v11 = 0;
		v20 = -val * T(t - 1);
		v21 = val;
	}
	friend bool operator ==(const Mat &lhs, const Mat &rhs) {
		return lhs.v10 == rhs.v10 && lhs.v11 == rhs.v11 && lhs.v20 == rhs.v20 && lhs.v21 == rhs.v21;
	}
	friend void tag_apply(Mat &cur, int l, int r, const Mat &x) {
		Mat res{};
		res.v10 = cur.v10 + cur.v11 * x.v10;
		res.v11 = cur.v11 * x.v11;
		res.v20 = cur.v20 + cur.v21 * x.v10 + x.v20;
		res.v21 = cur.v21 * x.v11 + x.v21;
		cur = res;
	}
}; /// end-hash

template<class T> /// start-hash
struct Vec {
	T v0, v1;
	Vec(T val = 0) { v0 = v1 = val; }
	friend Vec operator +(const Vec &lhs, const Vec &rhs) {
		Vec res{};
		res.v0 = lhs.v0 + rhs.v0;
		res.v1 = lhs.v1 + rhs.v1;
		return res;
	}
	void apply(T len, const Mat<T> &x) {
		v0 = v0 + v1 * x.v10 + len * x.v20;
		v1 = v1 * x.v11 + len * x.v21;
	}
	friend void info_apply(Vec &cur, int l, int r, const Mat<T> &x) { cur.apply(r - l + 1, x); }
	friend void info_apply(Vec &cur, const Mat<T> &x) { cur.apply(1, x); }
	T get_val(int t) const { return v1 * T(t) + v0; }
}; /// end-hash
