/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Suffix Array with sparse table answering lcp of suffices.
 * Usage: SA suf(s); // $s$ can be string or vector.
 * Time: O(|s| \log |s|) for construction. O(1) per query.
 * Status: tested on https://ac.nowcoder.com/acm/contest/33186/B, https://codeforces.com/gym/102994/problem/D, https://ac.nowcoder.com/acm/contest/33195/D, https://www.luogu.com.cn/problem/P4094, https://www.luogu.com.cn/problem/P7769.
 */

#include "suffix-array.cpp"

struct SA_lcp: SA {
	vector<vi> st;
	
	template<class T> SA_lcp(const T &s): SA(s) {
		assert(n > 0);
		st.assign(__lg(n) + 1, vi(n));
		st[0] = h;
		st[0].push_back(0); // just to make st[0] of size n.
		rep(i, 1, __lg(n)) rep(j, 0, n - (1 << i)) {
			st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
		}
	}
	// return lcp(suff_i, suff_j) for i != j.
	int lcp(int i, int j) {
		if (i == n || j == n) return 0;
		assert(i != j);
		int l = rank[i], r = rank[j];
		if (l > r) swap(l, r);
		int k = __lg(r - l);
		return min(st[k][l], st[k][r - (1 << k)]);
	}
};
