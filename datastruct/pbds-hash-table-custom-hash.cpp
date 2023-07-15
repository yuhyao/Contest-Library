#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;

using ull = unsigned long long;
const ull FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();

template<class A>
struct CustomHash {
	static ull splitmix64(A val) {
		ull x = static_cast<ull>(val);
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator ()(ull x) const {
		return splitmix64(x + FIXED_RANDOM);
	}
};

template<class A, class B>
using HashMap = gp_hash_table<A, B, CustomHash<A>>;