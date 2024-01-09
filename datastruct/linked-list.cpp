/**
 * Author: Yuhao Yao
 * Date: 22-07-23
 * Description: Linked List. Note that it is not O(1) if you use bruteforce to find the first remaining element.
 * Time: O(1) per erase.
 */
struct LinkedList {
	int n;
	vi pre, nxt;
	LinkedList(int n) : pre(n), nxt(n) {
		iota(all(pre), -1);
		iota(all(nxt), 1);
	}
	void erase(int pos) {
		int l = pre[pos], r = nxt[pos];
		if (l != -1) nxt[l] = r;
		if (r != n) pre[r] = l;
	}
};