namespace treap
{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    template<class T> T rnd() { return uniform_int_distribution<T>()(rng); }
    
    array<int,maxn+5> pri,ls,rs;
    array<int,maxn+5> mn,mx,sz;
    int tot;
    
    int newnode()
    {
        pri[++tot] = rnd<int>();
        ls[tot] = rs[tot] = 0;
        mn[tot] = mx[tot] = tot;
        sz[tot] = 1;
        return tot;
    }
    void init() { tot=0; }
    void pu(int i) 
    { 
        mx[i] = mn[i] = i;
        if(ls[i]) mn[i] = mn[ls[i]];
        if(rs[i]) mx[i] = mx[rs[i]];
        sz[i] = sz[ls[i]] + sz[rs[i]] + 1;
    }
    int join(int x,int y)
    {   // need that keys in treap x are smaller than keys in treap y.
        if(!x || !y) return x|y;
        if(pri[x]>pri[y]) {rs[x]=join(rs[x],y); pu(x); return x;}
        else {ls[y]=join(x,ls[y]); pu(y); return y;}
    }
    void split(int i,int &x,int &y,int k)
    {
        if(!i) {x=y=0; return;}
        if(k>=sz[ls[i]]+1) x=i; split(rs[i],rs[x],y,k-sz[ls[i]]-1);
        else y=i; split(ls[i],x,ls[y],k);
        pu(i);
    }
}