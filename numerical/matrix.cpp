/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Matrix struct. 
 *  $Gaussian(C)$ eliminates the first $C$ columns and returns the rank of matrix induced by first $C$ columns.
 *  $inverse()$ gives the inverse of the matrix.
 *  $SolveLinear(A, b)$ solves linear system $A x =  b$ for matrix $A$ and vector $b$.
 *  Besides, you need function $isZero$ for your template $T$.
 * Usage: For SolveLinear():
 *  bool isZero(double x) { return abs(x) <= 1e-9; } // global
 *  Matrix<double> A(3, 4);
 *  vector<double> b(3);
 *  ... // set values for A and b.
 *  vector<double> xs = SolveLinear(A, b);
 * Time: O(n m \min\{n, m\}) for Gaussian, inverse and SolveLinear.
 * Status: inverse() tested on https://ac.nowcoder.com/acm/contest/33187/J; 
 *  SolveLinear() tested on https://www.luogu.com.cn/problem/P6125.
 */
template<class T>
struct Matrix {
	using Mat = Matrix; /// start-hash
	using Vec = vector<T>;

	vector<Vec> a;

	Matrix(int n, int m) { 
		assert(n > 0 && m > 0);
		a.assign(n, Vec(m));
	}
	Matrix(const vector<Vec> &a): a(a) {
		assert(sz(a) > 0 && sz(a[0]) > 0);
	}

	Vec& operator [](int i) const { return (Vec&) a[i]; }
	/// end-hash

	Mat operator +(const Mat &b) const {
		int n = sz(a), m = sz(a[0]);
		Mat c(n, m);
		rep(i, 0, n - 1) rep(j, 0, m - 1) c[i][j] = a[i][j] + b[i][j];
		return c;
	}

	Mat operator -(const Mat &b) const {
		int n = sz(a), m = sz(a[0]);
		Mat c(n, m);
		rep(i, 0, n - 1) rep(j, 0, m - 1) c[i][j] = a[i][j] - b[i][j];
		return c;
	}

	Mat operator *(const Mat &b) const {
		int n = sz(a), m = sz(a[0]), l = sz(b[0]);
		assert(m == sz(b.a));
		Mat c(n, l);
		rep(i, 0, n - 1) rep(k, 0, m - 1) rep(j, 0, l - 1) c[i][j] += a[i][k] * b[k][j];
		return c;
	}

	Mat tran() const {
		int n = sz(a), m = sz(a[0]);
		Mat res(m, n);
		rep(i, 0, n - 1) rep(j, 0, m - 1) res[j][i] = a[i][j];
		return res;
	}

	// Eliminate the first C columns, return the rank of matrix induced by first C columns.
	int Gaussian(int C) { /// start-hash
		int n = sz(a), m = sz(a[0]), rk = 0;
		assert(C <= m);
		rep(c, 0, C - 1) {
			int id = rk;
			while (id < n && ::isZero(a[id][c])) id++;
			if (id == n) continue;
			if (id != rk) swap(a[id], a[rk]);

			T tmp = a[rk][c];
			for (auto &x: a[rk]) x /= tmp;
			rep(i, 0, n - 1) if (i != rk) {
				T fac = a[i][c];
				rep(j, 0, m - 1) a[i][j] -= fac * a[rk][j];
			}
			rk++;
		}
		return rk;
	} /// end-hash

	Mat inverse() const { /// start-hash
		int n = sz(a), m = sz(a[0]);
		assert(n == m);
		auto b = *this;

		rep(i, 0, n - 1) b[i].resize(n * 2, 0), b[i][n + i] = 1;
		assert(b.Gaussian(n) == n);
		for (auto &row: b.a) row.erase(row.begin(), row.begin() + n);
		return b;
	} /// end-hash

	friend pair<bool, Vec> SolveLinear(Mat A, const Vec &b) { /// start-hash
		int n = sz(A.a), m = sz(A[0]);
		assert(sz(b) == n);
		rep(i, 0, n - 1) A[i].push_back(b[i]);
		int rk = A.Gaussian(m);
		rep(i, rk, n - 1) if (::isZero(A[i].back()) == 0) return {0, Vec{}};
		Vec res(m);
		revrep(i, 0, rk - 1) {
			T x = A[i][m];
			int last = -1;
			revrep(j, 0, m - 1) if (::isZero(A[i][j]) == 0) {
				x -= A[i][j] * res[j];
				last = j;
			}
			if (last != -1) res[last] = x;
		}
		return {1, res};
	} /// end-hash
};
