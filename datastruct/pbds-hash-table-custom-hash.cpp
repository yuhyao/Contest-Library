#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;

struct CustomHash {
	using ull = unsigned long long;
	inline static const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
	static ull splitmix64(ull x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator ()(ull x) const {
		return splitmix64(x + FIXED_RANDOM);
	}
	size_t operator ()(pair<int, int> a) const {
		ull x = a.first + (ull(a.second) << 32);
		return splitmix64(x + FIXED_RANDOM);
	}
};

template<class A, class B>
using HashMap = gp_hash_table<A, B, CustomHash<A>>;