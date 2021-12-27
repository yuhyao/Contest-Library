struct FenwickSegmentTree
{
    #define MAXN (maxn*256)

    int n,m,tot;
    array<int,MAXN+5> ls,rs,a;
    array<int,maxn+5> rt;
    void init(int _n,int _m)
    {
        rep(i,1,tot) ls[i]=rs[i]=a[i]=0;
        n=_n; m=_m; tot=0;
        rep(i,1,n) rt[i]=0;
    }
    void add(int &i,int l,int r,int pos,int v)
    {
        if(!i) i=++tot;
        a[i]+=v;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(pos<=mid) add(ls[i],l,mid,pos,v);
        else add(rs[i],mid+1,r,pos,v);
    }
    int ask(int i,int l,int r,int ql,int qr)
    {
        if(i==0 || ql>r || l>qr) return 0;
        if(ql<=l && r<=qr) return a[i];
        int mid=(l+r)>>1;
        return ask(ls[i],l,mid,ql,qr)+ask(rs[i],mid+1,r,ql,qr);
    }
    void add(int x,int y,int v) //A[x][y]+=v
    {
        for(;x<=n;x+=x&-x) add(rt[x],1,m,y,v);
    }
    int ask(int x,int l,int r) // return A[1~x][l~r]
    {
        int res=0;
        for(;x;x-=x&-x) res+=ask(rt[x],1,m,l,r);
        return res;
    }
    void erase(int x)
    {
        for(;x<=n;x+=x&-x) rt[x]=0;
    }
};