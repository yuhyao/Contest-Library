/**
 * Author: Yuhao Yao
 * Date: 23-05-06
 * Description: Mo's algorithm which answers $M$ range queries on $\{a_0, a_1, \ldots, a_{N - 1}\}$ offline. You need to implement three functions $pointAdd$, $pointErase$ and $pointAsk$. $pointAdd(i)$ and $pointErase(i)$ corresponds to taking $a_i$ into / out of consideration. $pointAsk(i)$ corresponds to answering the $i$-th query.
 * Time: $O(n \sqrt{m} \cdot A + m \cdot B)$ where $pointAdd(i)$ and $pointErase(i)$ are $O(A)$ and $pointAsk$ is $O(B)$.
 * Status: tested on https://loj.ac/p/6273.
 */
template<class T>
vector<T> Mo(int n, const vector<pii> &qs, function<void(int)> pointAdd, function<void(int)> pointErase, function<T(int)> pointAsk) {
	int m = sz(qs);
	if (m == 0) return vector<T>{};
	int s = n / sqrt(m) + 0.5;
	vi inds(m); iota(all(inds), 0);
	sort(all(inds), [&](int i, int j) {
		auto [l1, r1] = qs[i];
		auto [l2, r2] = qs[j];
		return l1 / s != l2 / s ? l1 / s < l2 / s : r1 < r2;
	});

	vector<T> ans(m);
	int l = 0, r = -1;
	for (auto i : inds) {
		auto [ql, qr] = qs[i];
		while (r < qr) pointAdd(++r);
		while (r > qr) pointErase(r--);
		while (l < ql) pointErase(l++);
		while (l > ql) pointAdd(--l);
		ans[i] = pointAsk(i);
	}
	return ans;
}