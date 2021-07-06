template<class T> struct Dijkstra
{
    vector<pair<int,T>> e[maxn+5];
    int n;
    T dis[maxn+5];
    bool mark[maxn+5];
    void init(int _n)
    {
        n=_n;
        rep(i,1,n) e[i].clear();
    }
    void work(int s)
    {
        rep(i,1,n) dis[i]=inf;
        rep(i,1,n) mark[i]=0;
        dis[s]=0;
        priority_queue<pair<T,int> > pq;
        pq.push({0,s});
        while(pq.size())
        {
            auto [_,now]=pq.top(); pq.pop();
            if(mark[now]) continue; 
            mark[now]=1;
            for(auto [v,w]: e[now]) if(chmin(dis[v],dis[now]+w)) q.push({-dis[v],v});
        }
    }
};