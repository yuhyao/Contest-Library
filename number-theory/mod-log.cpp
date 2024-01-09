/**
 * Author: Yuhao Yao
 * Date: 22-10-25
 * Description: BSGS for discrete log. Formally, it solves $a ^ x \equiv b (\mod\, p)$ given integer $a, b$ and a prime number $p$. Returns an solution $x$ if there exists.
 * Time: O(\sqrt{p} \log p).
 * Status: tested on https://www.luogu.com.cn/problem/P3846.
 */
template<class mint>
pair<bool, int> mod_log(mint a, mint b) {
	int p = mint::get_mod();
	int sq = sqrt(p) + 0.5;
	while (1ll * sq * sq < p) sq++;
	mint c = 1;
	vector<pair<mint, int>> vec;
	rep(i, 1, sq) {
		c *= a;
		vec.emplace_back(b * c, -i);
	}
	sort(all(vec));

	mint d = 1;
	rep(i, 1, sq) {
		d *= c;
		auto it = lower_bound(all(vec), make_pair(d, -p));
		if (it != vec.end() && it->first == d) {
			return {true, i * sq + it->second};
		}
	}
	return {false, 0};
}
