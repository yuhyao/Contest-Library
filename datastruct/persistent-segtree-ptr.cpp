/**
 * Author: Yuhao Yao
 * Date: 24-01-08
 * Description: Persistent Segment Tree of range $[0, N - 1]$. Point apply and thus no lazy propogation.
 *  Always define a global $info\_apply$ function to tell segment tree how you apply modification. 
 *  Combine is set as + operation. If you use your own struct, then please define constructor and + operation.
 *  Note that using shared\_ptr is slow but prevent memory leak. Change to raw pointer if time limit is tight.
 * Usage: Point Add and Range Sum.
 *  void apply(int \&a, int b) { a += b; } // global
 *  ...
 *  PersistSegtree<int> pseg(10); // N = 10.
 *  using ptr = PersistSegtree<int>::ptr;
 *  ptr new_rt = pseg.point\_apply(nullptr, 9, 1); // add 1 to last position (position 9).
 *  int sum = pseg.range\_ask(new_rt, 7, 9); // ask the sum between position 7 and 9, wrt version new_rt.
 * Time: O(\log N) per operation.
 * Status: tested on https://codeforces.com/contest/1479/problem/D, https://www.luogu.com.cn/problem/P7361, https://www.luogu.com.cn/problem/P4094.
 */
template<class Info>
struct PersistSegtree {
	struct node { /// start-hash
		Info info;
		shared_ptr<node> ls, rs;
		node(Info _info = {}): info(_info), ls(nullptr), rs(nullptr) {}
	};
	using ptr = shared_ptr<node>;
	int n;
	ptr rt;

	PersistSegtree(int n, const ptr &_rt = nullptr): n(n), rt(_rt) { assert(n > 0); }

	template<class... T>
	PersistSegtree point_apply(int pos, const T&... val) {
		auto dfs = [&](auto &dfs, ptr &now, int l, int r) {
			now = make_shared<node>(now == nullptr ? node{} : *now); // change to new node when you want to use ptr = node*.
			if (l == r) {
				info_apply(now->info, val...);
				return;
			}
			int mid = (l + r) >> 1;
			if (pos <= mid) dfs(dfs, now->ls, l, mid);
			else dfs(dfs, now->rs, mid + 1, r);
			now->info = (now->ls ? now->ls->info : Info{}) + (now->rs ? now->rs->info : Info{});
		};
		ptr nrt = rt;
		dfs(dfs, nrt, 0, n - 1);
		return PersistSegtree(n, nrt);
	}

	Info range_ask(int ql, int qr) {
		Info res{};
		auto dfs = [&](auto &dfs, const ptr &now, int l, int r) {
			if (now == nullptr || qr < l || r < ql) return;
			if (ql <= l && r <= qr) {
				res = res + now->info;
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, now->ls, l, mid);
			dfs(dfs, now->rs, mid + 1, r);
		};
		dfs(dfs, rt, 0, n - 1);
		return res;
	} /// end-hash

	// lower_bound on prefix sums of difference between two versions $A$ and $B$.
	friend int lower_bound(const PersistSegtree &A, const PersistSegtree &B, Info val) { /// start-hash
		Info sum{};
		auto dfs = [&](auto &dfs, const ptr &tx, const ptr &ty, int l, int r) {
			if (l == r) return sum + (ty == nullptr ? Info{} : ty->info) - (tx == nullptr ? Info{} : tx->info) >= val ? l : l + 1;
			int mid = (l + r) >> 1;
			Info s = (ty->ls == nullptr ? Info{} : ty->ls->info) - (tx->ls == nullptr ? Info{} : tx->ls->info);
			if (sum + s >= val) return dfs(dfs, tx->ls, ty->ls, l, mid);
			else {
				sum = sum + s;
				return dfs(dfs, tx->rs, ty->rs, mid + 1, r);
			}
		};
		assert(A.n == B.n);
		return dfs(dfs, A.rt, B.rt, 0, A.n - 1);
	} /// end-hash
};