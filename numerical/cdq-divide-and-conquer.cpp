/**
 * Author: Yuhao Yao
 * Date: 23-03-25
 * Description: CDQ divde and conquer trick computes array $a_i = f \left (i, \sum_{j = 1}^i a_{i - j} b_j \right )$ where $a_0$ and $b_1, ..., b_{n - 1}$ is known. Note that argument $bs$ include $bs[0]$, though it is never used (so you are allowed to put arbitrary value there).
 * Usage: CDQ_DC<mint>(as, bs, [](int i, mint x) { return x; }); // for $a_i = \sum_{j = 1}^i a_{i - j} b_j$.
 * Time: O(N \log^2 N).
 * Status: tested on https://www.luogu.com.cn/problem/P4721.
 */
template<class T, class FFT = FFT<T>>
void CDQ_DC(vector<T> &as, const vector<T> &bs, const function<T(int, const T&)> &f) {
	vector<T> cs(sz(as));
	auto dfs = [&](auto &dfs, int l, int r) -> void {
		if (l == r) {
			if (l > 0) as[l] = f(l, cs[l]);
			return;
		}
		int mid = (l + r) >> 1;
		dfs(dfs, l, mid);
		int n = r - l + 1;
		vector<T> xs(mid - l + 1), ys(n);
		rep(i, l, mid) xs[i - l] = as[i];
		rep(i, 0, n - 1) ys[i] = bs[i];
		auto zs = FFT::conv(xs, ys);
		rep(i, mid + 1, r) cs[i] += zs[i - l];
		dfs(dfs, mid + 1, r);
	};
	dfs(dfs, 0, sz(as) - 1);
}