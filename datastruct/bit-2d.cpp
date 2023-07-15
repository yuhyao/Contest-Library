/**
 * Author: Yuhao Yao
 */

template<class T> struct BIT2D {
	int n, m;
	vector<vector<T>> a;

	BIT2D(int n, int m): n(n), m(m), a(n + 1, vector<T>(m + 1)) {}

	void add(int x, int y, T val) {
		for (int i = x + 1; i <= n; i += i & -i)
			for (int j = y + 1; j <= m; j += j & -j)
				a[i][j] += val;
	}
	T ask(int x, int y) {
		T ans{};
		for (int i = x + 1; i; i -= i & -i)
			for (int j = y + 1; j; j -= j & -j)
				ans += a[i][j];
		return ans;
	}
	T ask(int x1, int y1, int x2, int y2) {
		return ask(x2, y2) - ask(x1 - 1, y2) - ask(x2, y1 - 1) + ask(x1 - 1, y1 - 1);
	}
};
