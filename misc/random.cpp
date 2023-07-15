mt19937_64 rng{chrono::steady_clock::now().time_since_epoch().count()};
template<class T> T myrand(T a, T b) { return uniform_int_distribution<T>(a, b)(rng); }
template<class T> T myrand() { return uniform_int_distribution<T>()(rng); }