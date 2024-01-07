template<class T> 
struct Info {
	T val;
	Info(T val = 0): val(val) {}
	friend Info operator +(const Info &a, const Info &b) {
		return a.val + b.val;
	}
	friend void info_apply(Info &cur, int l, int r, const T &x) {
		cur.val += x * (r - l + 1);
	}
};

template<class T> 
void tag_apply(T &cur, int l, int r, const T &x) {
	cur += x;
}