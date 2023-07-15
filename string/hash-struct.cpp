/**
 * Author: Yuhao Yao
 * Date: 23-05-01
 * Description: Hash struct. $1000000007$ and $1000050131$ are good moduli.
 * Status: tested on https://ac.nowcoder.com/acm/contest/33192/I, https://ac.nowcoder.com/acm/contest/33193/I.
 */
template<int m1, int m2>
struct Hash {
	int x, y;
	Hash(ll a, ll b): x(a % m1), y(b % m2) {
		if (x < 0) x += m1;
		if (y < 0) y += m2;
	}
	Hash(ll a = 0): Hash(a, a) {}

	using H = Hash;
	static int norm(int x, int mod) { return x >= mod ? x - mod : x < 0 ? x + mod : x; }
	H& operator +=(H b) { x = norm(x + b.x, m1); y = norm(y + b.y, m2); return *this; }
	H& operator -=(H b) { x = norm(x - b.x, m1); y = norm(y - b.y, m2); return *this; }
	H& operator *=(H b) { x = 1ll * x * b.x % m1; y = 1ll * y * b.y % m2; return *this; }
	friend H operator +(H a, H b) { return a += b; }
	friend H operator -(H a, H b) { return a -= b; }
	friend H operator *(H a, H b) { return a *= b; }
	
	friend bool operator ==(H a, H b) { return tie(a.x, a.y) == tie(b.x, b.y); }
	friend bool operator !=(H a, H b) { return tie(a.x, a.y) != tie(b.x, b.y); }
	friend bool operator <(H a, H b) { return tie(a.x, a.y) < tie(b.x, b.y); }

	friend string to_string(H a) { return to_string(make_pair(a.x, a.y)); }
};