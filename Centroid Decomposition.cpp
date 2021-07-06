struct Centroid_Decomposition
{
    array<int,maxn+5> sz,Msz,level,cfa;
    array<bool,maxn+5> vis;
    int cdis[maxn+5][20]; //distance to center.
    int rt,sum;
    void getrt(int now,int fa)
    {
        sz[now]=1;
        Msz[now]=0;
        for(auto v: e[now])
        {
            if(v==fa || vis[v]) continue;
            getrt(v,now);
            sz[now]+=sz[v];
            Msz[now]=max(Msz[now],sz[v]);
        }
        Msz[now]=max(Msz[now],sum-sz[now]);
        if(Msz[now]<Msz[rt]) rt=now;
    }
    void dfs(int now,int fa,int dep,int lvl)
    {
        cdis[now][lvl]=dep;
        for(auto v: e[now]) if(v!=fa && vis[v]==0) dfs(v,now,dep+1,lvl);
    }
    void solve(int now,int fa,int lvl)
    {
        cfa[now]=fa; level[now]=lvl; cdis[now][lvl]=0;
        vis[now]=1; 

        int SZ=sum;
        for(auto v: e[now]) if(vis[v]==0)
        {
            sum=sz[v]<sz[now]?sz[v]:SZ-sz[now];
            rt=0; getrt(v,0);
            dfs(v,now,1,lvl);
            solve(rt,now,lvl+1);
        }
    }
    void build(int N)
    {
        Msz[0]=inf;
        rep(i,1,N) vis[i]=0;
        sum=N; rt=0; getrt(1,0);
        solve(rt,0,0);
    }
}cd;