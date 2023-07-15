/**
 * Author: Yuhao Yao
 * Date: 22-09-27
 * Description: Fenwick Tree.
 */
template<class T> struct BIT {
	int n;
	vector<T> a;

	BIT(int n): n(n), a(n + 1, 0) {}

	void Add(int i, T x) { 
		for (++i; i <= n; i += i & -i) a[i] += x;
	}

	T Ask(int i) {
		T ans{};
		for (++i; i; i -= i & -i) ans += a[i];
		return ans;
	}

	T rangeAsk(int l, int r) { return Ask(r) - Ask(l - 1); }

	// assuming prefix sums are non-decreasing, finds the first pos such that ask(pos) >= x.
	int lower_bound(T x) {
		assert(n > 0);
		int pos = 0;
		for (int h = 1 << __lg(n); h; h >>= 1) {
			if ((pos | h) <= n && a[pos | h] < x) {
				pos |= h;
				x -= a[pos];
			}
		}
		return pos;
	}
};