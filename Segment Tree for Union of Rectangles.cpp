struct Segtree
{
    #define ls i*2
    #define rs i*2+1
    array<int,maxn*4+5> a,lz;
    void pu(int i,int l,int r) 
    {
        if(lz[i]) a[i]=r-l+1;
        else a[i]=(l==r?0:a[ls]+a[rs]);
    }
    void build(int i,int l,int r)
    {
        a[i]=lz[i]=0;
        if(l<r)
        {
            int mid=(l+r)>>1;
            build(ls,l,mid);
            build(rs,mid+1,r);
        }
    }
    void add(int i,int l,int r,int ql,int qr,const int &x)
    {
        if(ql<=l && r<=qr)
        {
            lz[i]+=x;
            pu(i,l,r);
            return;
        }
        if(qr<l || r<ql) return;
        int mid=(l+r)>>1;
        add(ls,l,mid,ql,qr,x);
        add(rs,mid+1,r,ql,qr,x);
        pu(i,l,r);
    }
    #undef ls
    #undef rs
};