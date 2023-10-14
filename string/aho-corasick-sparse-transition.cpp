/**
 * Author: Yuhao Yao
 * Date: 22-10-16
 * Description: Aho_Corasick Automaton of strings $s_0, ..., s_{n - 1}$. $s_i$ can be string or vector<int>.
 * Usage: Aho_Corasick ac; for strings or vectors. Call ac.build() after you insert all $s_0, ..., s_{n - 1}$.
 * Time: O(\sum_{i = 0}^{n - 1} |s_i|).
 * Status: tested on http://ejudge.opencup.org/~ejudge/team.cgi?contest_id=2744 (problem M), https://www.luogu.com.cn/problem/P6125.
 */
struct Aho_Corasick {
	struct node {
		map<int, int> nxt;
		int fail = -1;
		int cnt = 0;
	};
	vector<node> t;

	Aho_Corasick(): t(1) {}

	template<class T>
	int insert(const T &s) {
		int now = 0;
		for (auto c : s) {
			if (t[now].nxt.count(c) == 0) {
				t.emplace_back();
				t[now].nxt[c] = sz(t) - 1;
			}
			now = t[now].nxt[c];
		}
		t[now].cnt++;
		return now;
	}

	void build() {
		vi que{0};
		rep(ind, 0, sz(que) - 1) {
			int now = que[ind];
			if (now != 0) t[now].cnt += t[t[now].fail].cnt;
			for (auto [c, v] : t[now].nxt) {
				int p = t[now].fail;
				while (p != -1 && t[p].nxt.count(c) == 0) p = t[p].fail;
				t[v].fail = p == -1 ? 0 : t[p].nxt[c];
				que.push_back(v);
			}
		}
	}

	int transit(int p, int c) {
		while (p != -1 && t[p].nxt.count(c) == 0) p = t[p].fail;
		return p == -1 ? 0 : t[p].nxt[c];
	}
};