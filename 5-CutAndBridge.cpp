vi e[maxn+5];
int dep[maxn+5],low[maxn+5],bridge,cut;

void dfs(int now,int fa)
{
    bool mark_fa=0,is_cut=0;
    int son_cnt=0;
    dep[now]=dep[fa]+1;
    low[now]=dep[now];
    // assume no multiple edge and self loop
    for(auto v: e[now]) if(v!=fa) 
    {
        if(dep[v]) low[now]=min(low[now],dep[v]);
        else
        {
            son_cnt++;
            dfs(v);
            low[now]=min(low[now],low[v]);
            if(low[v]==dep[v]) bridge++;
            if(low[v]>=dep[now] && dep[now]>1) is_cut=1;
        }
    }
    if(fa==0 && son_cnt>1) cut++;
    else if(is_cut) cut++;
    return;
}
int main()
{
    memset(dep,0,sizeof dep);
    dfs(1,0);
    return 0;
}
