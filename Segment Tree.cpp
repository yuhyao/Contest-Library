// Range add & range query.
template<class T> struct Segtree
{
    #define ls i*2
    #define rs i*2+1
    array<T,maxn*4+5> a,lz;
    void push(int i,int l,int r,T x)
    {
        a[i]+=x*(r-l+1);
        lz[i]+=x;
    }
    void pu(int i) {a[i]=a[ls]+a[rs];}
    void pd(int i,int l,int r)
    {
        if(lz[i])
        {
            int mid=(l+r)>>1;
            push(ls,l,mid,lz[i]);
            push(rs,mid+1,r,lz[i]);
            lz[i]=0;
        }
    }
    void build(int i,int l,int r)
    {
        lz[i]=0;
        if(l==r) a[i]=0;
        else
        {
            int mid=(l+r)>>1;
            build(ls,l,mid);
            build(rs,mid+1,r);
            pu(i);
        }
    }
    void add(int i,int l,int r,int ql,int qr,const T &x)
    {
        if(ql<=l && r<=qr)
        {
            push(i,l,r,x);
            return;
        }
        if(qr<l || r<ql) return;
        int mid=(l+r)>>1;
        pd(i,l,r);
        add(ls,l,mid,ql,qr,x);
        add(rs,mid+1,r,ql,qr,x);
        pu(i);
    }
    T ask(int i,int l,int r,int ql,int qr)
    {
        if(ql<=l && r<=qr) return a[i];
        if(qr<l || r<ql) return 0;
        int mid=(l+r)>>1;
        pd(i,l,r);
        return ask(ls,l,mid,ql,qr)+ask(rs,mid+1,r,ql,qr);
    }
    #undef ls
    #undef rs
};
