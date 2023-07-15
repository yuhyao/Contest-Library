/**
 * Author: Yuhao Yao
 * Date: 22-10-25
 * Description: Sieve for prime numbers / multiplicative functions in $\{1, 2, ..., N\}$ in linear time.
 * Time: O(N).
 * Status: tested on https://official.contest.yandex.com/opencupXXII/contest/37831/problems/B/.
 */
struct LinearSieve {
	vi ps, minp;
	vi d, facnum, phi, mu;
	LinearSieve(int n): minp(n + 1), d(n + 1), facnum(n + 1), phi(n + 1), mu(n + 1) {
		facnum[1] = phi[1] = mu[1] = 1;
		rep(i, 2, n) {
			if (minp[i] == 0) {
				ps.push_back(i);
				minp[i] = i;
				d[i] = 1;
				facnum[i] = 2;
				phi[i] = i - 1;
				mu[i] = -1;
			}
			for (auto p: ps) {
				ll v = 1ll * i * p;
				if (v > n) break;
				minp[v] = p;
				if (i % p == 0) {
					d[v] = d[i] + 1;
					facnum[v] = facnum[i] / (d[i] + 1) * (d[v] + 1);
					phi[v] = phi[i] * p;
					mu[v] = 0;
					break;
				}
				d[v] = 1;
				facnum[v] = facnum[i] * 2;
				phi[v] = phi[i] * (p - 1);
				mu[v] = -mu[i];
			}
		}
	}
};
