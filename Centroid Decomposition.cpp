// vertices' indices start from 1.
struct Centroid_Decomposition
{
    array<int,maxn+5> sz;
    array<bool,maxn+5> vis;
    vi anc[maxn+5]; // ancestors in centroid tree, including itself.
    vi cdis[maxn+5]; // distances to ancestors in centroid tree, not necessarily monotone.
    void solve(int _,int SZ)
    {
        int mn = inf, rt = -1;
        function<void(int,int)> getrt = [&](int now,int fa) {
            sz[now]=1;
            int mx = 0;
            for(auto v: e[now]) if(v!=fa && vis[v]==0)
            {
                getrt(v,now);
                sz[now]+=sz[v];
                chmax(mx,sz[v]);
            }
            chmax(mx,SZ-sz[now]);
            if(chmin(mn,mx)) rt=now;
        };
        getrt(_,0); vis[rt]=1; 

        function<void(int,int,int)> dfs = [&](int now,int fa,int dep) {
            anc[now].pb(rt); cdis[now].pb(dep);
            for(auto v: e[now]) if(v!=fa && vis[v]==0) dfs(v,now,dep+1);
        };
        dfs(rt,0,0);
        // start your work here.

        for(auto v: e[rt]) if(vis[v]==0) solve(v, sz[v]<sz[rt]?sz[v]:SZ-sz[rt]);
    }
    void build(int N)
    {
        rep(i,1,N) vis[i]=0;
        rep(i,1,N) anc[i].clear();
        rep(i,1,N) cdis[i].clear();
        solve(1,N);
    }
}cd;