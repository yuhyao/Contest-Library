// indices start from 1.
struct BCC
{
    #define maxm 200000
    array<int,maxn+5> dep,low;
    array<pii,maxm+5> sta;
    vi e[maxn+5];
    vector<pii> scc[maxm+5];
    int cnt,top,scc_cnt;

    void init(int n)
    {
        cnt=top=scc_cnt=0;
        rep(i,1,n) dep[i]=0;
        rep(i,1,n) e[i].clear();
    }
    void addedge(int x,int y) {e[x].pb(y); e[y].pb(x);}
    // no multiple edge and self-loop
    void dfs(int now,int fa)
    {
        low[now]=dep[now]=dep[fa]+1; 
        for(auto v: e[now]) if(v!=fa)
        {
            if(dep[v]>dep[now]) continue;
            int top_tmp=top;
            sta[++top]={now,v};
            if(dep[v]==0) 
            {
                dfs(v,now);
                chmin(low[now],low[v]);
                if(low[v]>=dep[now]) // now is a cut vertex.
                {
                    scc[++scc_cnt].clear();
                    while(top>top_tmp) scc[scc_cnt].pb(sta[top--]);
                }
            }
            else chmin(low[now],dep[v]);
        }
    }
    #undef maxm
}bcc;