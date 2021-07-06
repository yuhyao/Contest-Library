struct BCC
{
    #define maxm 200000
    array<int,maxn+5> dep,low;
    array<EDGE,maxm+5> sta;
    vector<EDGE> scc[maxn+5];
    int cnt,top,scc_cnt;

    void init(int n)
    {
        cnt=top=scc_cnt=0;
        rep(i,1,n) dep[i]=0;
    }
    // no multiple edge and self-loop
    void dfs(int now,int fa)
    {
        dep[now]=dep[fa]+1; low[now]=dep[now];
        for(auto [v,w]: e[now]) if(v!=fa)
        {
            if(dep[v]>dep[now]) continue;
            int top_tmp=top;
            sta[++top]=EDGE{now,v,w};
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