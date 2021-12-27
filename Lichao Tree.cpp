struct P
{
    int x,y;
    P():x(0),y(0){};
    P(int x,int y):x(x),y(y){}
    void in() {scanf("%d%d",&x,&y);}
    P operator -(const P &a) const {return P(x-a.x,y-a.y);}
    ll cross(const P &a) const {return 1ll*x*a.y-1ll*y*a.x;}
}p[maxn+5],dir[maxn+5];

template<class T> inline int sgn(const T &x) {return (x>0)-(x<0);}
int cmp(int a,int b,int t)
{   // return sgn(seg_a(t) - seg_b(t)).
    if(a==0 || b==0)
    {
        return a==0 && b ? -1 : 1;
    }
    P &A = p[a], &DA = dir[a];
    P &B = p[b], &DB = dir[b];
    return sgn(1ll*A.y*DA.x*DB.x + 1ll*DA.y*DB.x*(t-A.x) - (1ll*B.y*DA.x*DB.x + 1ll*DB.y*DA.x*(t-B.x)));
}

struct Lichaotree
{
    #define ls i*2
    #define rs i*2+1
    array<int,maxn*4+5> a;
    void build(int i,int l,int r)
    {
        if(l==r) a[i]=0; // currently no dominating segments.
        else
        {
            int mid=(l+r)>>1;
            build(ls,l,mid);
            build(rs,mid+1,r);
        }
    }
    void upd(int i,int l,int r,int ql,int qr,int v)
    {
        int mid=(l+r)>>1;
        if(ql<=l && r<=qr)
        {
            int &u = a[i];
            if(cmp(u,v,mid)<0) swap(u,v);
            if(l==r) return;
            auto rev = dir[u].cross(dir[v]);
            if(rev<0) upd(ls,l,mid,ql,qr,v);
            if(rev>0) upd(rs,mid+1,r,ql,qr,v);
            return;
        }
        if(qr<l || r<ql) return;
        upd(ls,l,mid,ql,qr,v);
        upd(rs,mid+1,r,ql,qr,v);
    }
    int ask(int i,int l,int r,int pos)
    {
        if(l==r) return a[i];
        int mid=(l+r)>>1;
        int res = pos<=mid ? ask(ls,l,mid,pos) : ask(rs,mid+1,r,pos);
        if(res==0) res = a[i];
        else if(a[i])
        {
            if(cmp(res,a[i],pos)<0) res = a[i];
            else if(cmp(res,a[i],pos)==0 && a[i]<res) res = a[i]; 
        }
        return res;
    }
    #undef ls
    #undef rs
};