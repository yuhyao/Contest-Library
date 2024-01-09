/**
 * Author: Yuhao Yao
 * Date: 23-02-04
 * Description: Add lines of the form $kx + b$ and get the maximum value at arbitrary $x$.
 * Time: O(\log N)
 * Status: Tested on https://codeforces.com/contest/932/problem/F.
 */
template<class T>
struct Line {
	T k;
	mutable T b, p;
	bool operator <(const Line &o) const { return k < o.k; }
	bool operator <(const T &x) const { return p < x; }
	friend string to_string(const Line &l) { return "(" + to_string(l.k) + ", " + to_string(l.b) + ", " + to_string(l.p) + ")"; }
};

template<class T>
class LineContainer : private set<Line<T>, less<>> {
	static constexpr bool isInt = is_integral_v<T>;
	static constexpr T inf = numeric_limits<T>::max();
public:
	using typename set<Line<T>, less<>>::iterator;
	using set<Line<T>, less<>>::begin;
	using set<Line<T>, less<>>::end;
	using set<Line<T>, less<>>::size;
private:
	using set<Line<T>, less<>>::insert;
	using set<Line<T>, less<>>::erase;
	using set<Line<T>, less<>>::lower_bound;
public:	
	void add(T k, T b) {
		auto fix = [&](iterator it) -> bool {
			if (next(it) == end()) {
				it->p = inf;
				return 0;
			}

			auto div = [](T a, T b) { // floored division
				if (isInt) return a / b - ((a ^ b) < 0 && a % b);
				else return a / b;
			};
			
			it->p = div(next(it)->b - it->b, it->k - next(it)->k);
			return it->p >= next(it)->p;
		};

		auto it = insert({k, b, 0}).first;
		it->b = max(it->b, b);

		while (fix(it)) erase(next(it));
		if (it == begin()) return;
		else if (fix(prev(it))) {
			it = erase(it);
			fix(prev(it));
		} else {
			it = prev(it);
			while (it != begin() && prev(it)->p >= it->p) {
				it = prev(erase(it));
				fix(it);
			}
		}
	}

	T get(T x) const {
		assert(size() > 0);
		auto l = *lower_bound(x);
		return l.k * x + l.b;
	}
};