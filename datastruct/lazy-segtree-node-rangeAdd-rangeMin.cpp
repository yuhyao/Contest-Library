template<class T>
struct Info {
	T val;
	int id;
	Info(T val = numeric_limits<T>::max(), int id = -1): val(val), id(id) {}
	friend Info operator +(const Info &a, const Info &b) {
		return a.val < b.val ? a : b;
	}
	friend void InfoApply(Info &cur, int l, int r, const T &x) {
		cur.val += x;
	}
};

template<class T> 
void TagApply(T &cur, int l, int r, const T &x) {
	cur += x;
}