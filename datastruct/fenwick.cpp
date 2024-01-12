/**
 * Author: Yuhao Yao
 * Date: 24-01-07
 * Description: Fenwick Tree.
 */
template<class T>
struct Fenwick {
	int n; /// start-hash
	vector<T> as;

	Fenwick(int n) : n(n), as(n + 1, 0) {}

	void add(int i, T x) { 
		for (i++; i <= n; i += i & -i) as[i] += x;
	}

	T ask(int i) {
		T ans{};
		for (i++; i; i -= i & -i) ans += as[i];
		return ans;
	}

	T range_ask(int l, int r) { return ask(r) - ask(l - 1); }
	/// end-hash
	// assuming prefix sums are non-decreasing, finds the first pos such that ask(pos) >= x.
	int lower_bound(T x) { /// start-hash
		assert(n > 0);
		int pos = 0;
		for (int h = 1 << __lg(n); h; h >>= 1) {
			if ((pos | h) <= n && as[pos | h] < x) {
				pos |= h;
				x -= as[pos];
			}
		}
		return pos;
	} /// end-hash
};
