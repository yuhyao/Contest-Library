/**
 * Author: Yuhao Yao
 * Description: Easy implemented matrix multiplication.
 */

const int MatN = 2;
using Vec = array<int, MatN>;
using Mat = array<Vec, MatN>;

Mat operator *(const Mat &a, const Mat &b) {
	Mat c{};
	rep(i, 0, MatN - 1) rep(k, 0, MatN - 1) rep(j, 0, MatN - 1)
		c[i][j] += a[i][k] * b[k][j];
	return c;
}

Mat qp(Mat a, ll k) {
	Mat res{};
	rep(i, 0, MatN - 1) res[i][i] = 1;
	for(; k; k >>= 1, a = a * a) if(k & 1) res = res * a;
	return res;
}
