mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> T rnd() { return uniform_int_distribution<T>()(rng); }

struct treap 
{
    const int pri;
    treap *ls = NULL, *rs = NULL;
    int sz = 1, val, mn, mx;

    treap(int v = 0) : pri(rnd<int>()) { val = mn = mx = v;}
    ~treap() 
    {
        delete ls;
        delete rs;
    }
    void pushup() 
    {
        sz = 1 + (ls ? ls->sz : 0) + (rs ? rs->sz : 0);
        mn = ls ? ls->mn : val;
        mx = rs ? rs->mx : val;
    }
    void pushdown() {} // Lazy update
    static treap* join(treap* a,treap* b) 
    {
        if(!a || !b) return a ? a : b;
        treap* res = ((a->pri < b->pri) ? a : b);
        res->pushdown();
        if(res==a) a->rs = join(a->rs,b);
        else b->ls = join(a,b->ls);
        res->pushup();
        return res;
    }
    static void split(treap* now,treap* &x,treap* &y,int k) 
    {
        if(!now) {x = y = NULL; return;}
        int lsz = 1 + (now->ls ? now->ls->sz : 0);
        now->pushdown();
        if(k>=lsz) x = now, split(now->rs, x->rs, y, k - lsz);
        else y = now, split(now->ls, x, y->ls, k);
        now->pushup();
    }
};