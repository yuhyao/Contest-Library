// interval addition and interval minimum value query.
// Note: Need test!!!
template<class T>struct Persistent_segtree
{
    #define MAXN (maxn*4+(MAXQ*(__lg(maxn)+1)*4))
    int n, k, last, tot;
    array<int,MAXN+5> ls,rs;
    array<T,MAXN+5> a;
    array<T,MAXN+5> lz;

    int clone(int now)
    {
        if(now>last) return now;
        ++tot;
        ls[tot] = ls[now];
        rs[tot] = rs[now];
        a[tot] = a[now];
        lz[tot] = lz[now];
        return tot;
    }
    void push(int &now,T val)
    {
        now = clone(now);
        a[now] += val;
        lz[now] += val;
    }
    void pu(int now) { a[now] = min(a[ls[now]],a[rs[now]]); }
    void pd(int now)
    {
        if(lz[now])
        {
            push(ls[now],lz[now]);
            push(rs[now],lz[now]);
            lz[now] = 0;
        }
    }
    void build(int &now,int l,int r)
    {   // We initialize all values with 0 here.
        now = ++tot;
        lz[tot] = 0;
        if(l==r) a[tot] = 0;
        else
        {
            int mid=(l+r)>>1;
            build(ls[now],l,mid);
            build(rs[now],mid+1,r);
            pu(now);
        }
    }
    void add(int &now,int l,int r,const int &ql,const int &qr,const T &val)
    {
        if(ql<=l && r<=qr) return push(now,val);
        if(r<ql || qr<l) return;
        now = clone(now);
        int mid = (l+r)>>1;
        pd(now);
        add(ls[now],l,mid,ql,qr,val);
        add(rs[now],mid+1,r,ql,qr,val);
        pu(now);
    }
    T ask(int now,int l,int r,int ql,int qr)
    {   // Here we replace the old nodes (not keeping the old version and making a copy), but it is safe to do this.
        if(ql<=l && r<=qr) return a[now];
        if(r<ql || qr<l) return inf;
        int mid=(l+r)>>1;
        pd(now);
        return min(ask(ls[now],l,mid,ql,qr),ask(rs[now],mid+1,r,ql,qr));
    }
    int init(int _n)
    {   // Return the initial root node.
        n = _n;
        tot = last = 0;
        int rt = 0;
        build(rt,1,n);
        return rt;
    }
    int RangeAdd(int rt,int ql,int qr,int op,int id,T val)
    {   // Return root node of the newest version.
        last = tot;
        add(rt,1,n,ql,qr,op,id,val);
        return rt;
    }
    T Rangeask(int rt,int ql,int qr)
    {
        last = tot;
        return ask(rt,1,n,ql,qr);
    }
    #undef MAXN
};