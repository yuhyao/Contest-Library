// indices start from 1.
struct dsu_on_tree
{
    vi e[maxn+5];
    int sz[maxn+5],dfn,tin[maxn+5],tout[maxn+5],ver[maxn+5];
    void init(int _n) {rep(i,1,_n) e[i].clear();}
    void addedge(int x,int y) 
    {
        e[x].pb(y);
        e[y].pb(x);
    }
    void calsz(int now,int fa)
    {
        sz[now]=1;
        for(auto v: e[now]) if(v!=fa) calsz(v,now),sz[now]+=sz[v];
    }
    void dfs(int now,int fa,bool keep)
    {
        tin[now]=++dfn; ver[dfn]=now;
        int mx=0,hv=-1;
        for(auto v: e[now]) if(v!=fa && chmax(mx,sz[v])) hv=v;
        for(auto v: e[now]) if(v!=fa && v!=hv) dfs(v,now,0);
        if(hv!=-1) dfs(hv,now,1);

        // here: insert the vertex now & update the answer.

        for(auto v: e[now]) if(v!=fa && v!=hv)
        {
            // here: insert vertices in the light subtrees & update the answer.
        }
        tout[now]=dfn;
        if(keep==0) rep(x,tin[now],tout[now]) cnt[msk[ver[x]]]=0;
    }
    void work(int rt)
    {
        calsz(rt,0);
        dfs(rt,0,1);
    }
}dsu;