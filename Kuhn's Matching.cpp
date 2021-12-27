struct Kuhn
{
    // indices start from 1.
    int n,m; // n=size of X, m=size of Y.
    vi e[maxn+5]; // from X part to Y part.
    int from[maxn+5]; // record the matched vertex for vertices in Y.
    bool used[maxn+5];

    void init(int _n,int _m) 
    {
        n=_n, m=_m;
        rep(i,1,n) e[i].clear();
    }
    bool match(int u)
    {
        for(auto v: e[u]) if(used[v]==0)
        {
            used[v]=1;
            if(from[v]==-1 || match(from[v]))
            {
                from[v]=u;
                return 1;
            }
        }
        return 0;
    }
    int work()
    {
        int res=0;
        rep(i,1,m) from[i]=-1;
        rep(i,1,n)
        {
            rep(i,1,m) used[i]=0;
            res+=match(i);
        }
        return res;
    }
};
