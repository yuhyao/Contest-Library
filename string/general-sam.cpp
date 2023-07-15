/**
 * Author: Yuhao Yao
 * Date: 22-10-30
 * Description: General Suffix Automaton of a given Trie $T$. (Using map to store sons makes it 2$\sim$3 times slower but it should be fine in most cases. If $T$ is of size > $10^6$, then you should think of using int[] instead of map.)
 *  $len$ is the length of the longest substring corresponding to the state. 
 *  $fa$ is the father in the reversed prefix tree. Note that fa[i] < i doesn't hold.
 *  $occ$ should be set manually when building Trie $T$.
 *  root is 0.
 * Usage: GSAM sam(T); // $T$ should be vector<GSAM::node>.
 * Time: O(|T|).
 * Status: tested on https://www.luogu.com.cn/problem/P6139, https://nanti.jisuanke.com/t/42551, https://codeforces.com/contest/316/problem/G3.
 */

struct GSAM {
	struct node {
		map<int, int> nxt; // change this if TL or ML is tight.
		int fa, len; // keep fa = -1 and len = 0 initially.
		int occ; // should be assigned when building the trie.
		node() { fa = -1; len = occ = 0; }
	};

	vector<node> t;
	GSAM(const vector<node> &trie): t(trie) { // swap(t, trie) here if TL or ML is tight
		auto ins = [&](int now, int c) {
			int last = t[now].nxt[c];
			t[last].len = t[now].len + 1;
			now = t[now].fa;
			while (now != -1 && t[now].nxt.count(c) == 0) {
				t[now].nxt[c] = last;
				now = t[now].fa;
			}
			if (now == -1) t[last].fa = 0;
			else {
				int p = t[now].nxt[c];
				if (t[p].len == t[now].len + 1) t[last].fa = p;
				else { // clone a node np from node p.
					t.emplace_back();
					int np = sz(t) - 1;
					for (auto [i, v]: t[p].nxt) if (t[v].len > 0) {
						t[np].nxt[i] = v;
					}
					t[np].fa = t[p].fa;
					t[np].len = t[now].len + 1;

					t[last].fa = t[p].fa = np;
					while (now != -1 && t[now].nxt.count(c) && t[now].nxt[c] == p) {
						t[now].nxt[c] = np;
						now = t[now].fa;
					}
				}
			}
		};

		vi que{0};
		rep(ind, 0, sz(que) - 1) {
			int now = que[ind];
			vi cs;
			for (auto [c, v]: t[now].nxt) {
				cs.push_back(c);
				que.push_back(v);
			}
			for (auto c: cs) ins(now, c);
		}
	}
};
