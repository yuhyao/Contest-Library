//indices start from 1.
struct Euler_tour
{
    int n,tot;
    vector<pii> e[maxn+5];
    void init(int _n)
    {
        n=_n; tot=0;
        rep(i,1,n) e[i].clear();
    }
    void addedge(int x,int y)
    {
        e[x].pb({y,++tot}); e[y].pb({x,tot});
    }
    void work(int n,int src,vi &res)
    {
        res.clear();
        stack<int> sta; sta.push(src);
        vi cur(n+1),vis(tot+1);

        while(sta.size())
        {
            int now=sta.top(),fin=1;
            for(int &i=cur[now];i<sz(e[now]);)
            {
                auto [v,id]=e[now][i]; i++;
                if(vis[id]) continue;
                vis[id]=1;
                sta.push(v);
                fin=0;
                break;
            }
            if(fin) res.pb(now), sta.pop();
        }
    }
}eu;

// indices: [0, n].
struct Euler_tour_recursive
{
    int n,tot;
    vector<pii> e[maxn+5];
    void init(int _n)
    {
        n=_n; tot=0;
        rep(i,0,n) e[i].clear();
    }
    void addedge(int x,int y)
    {
        e[x].pb({y,++tot}); e[y].pb({x,tot});
    }
    vi work()
    {
        vi path;
        vi cur(n+1),vis(tot+1);
        function<void(int)> dfs = [&](int now) {
            static vi cur(n+1), vis(tot+1);
            for(int &i=cur[now];i<sz(e[now]);)
            {
                auto [v,id]=e[now][i]; i++;
                if(vis[id]) continue;
                vis[id]=1;
                dfs(v);
                path.pb(id);
            }
        };
        rep(i,0,n) dfs(i);
        return path;
    }
}eu;