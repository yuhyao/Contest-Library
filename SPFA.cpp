using cost_t = long long;
const cost_t MC = 1ll<<60;

cost_t dis[maxn+5];
vector<pair<int,cost_t> > e[maxn+5];
void spfa(int n,int src)
{
    rep(i,1,n) dis[i]=MC;
    vi mark(n+1,0);
    deque<int> q;
    q.pb(src); dis[src]=0; mark[src]=1;
    while(q.size())
    {
        int now=q.front(); q.pop_front();
        mark[now]=0;
        for(auto [v,w]: e[now]) if(chmin(dis[v],dis[now]+w))
        {
            if(mark[v]==0) 
            {
                if(q.size() && dis[v]<dis[q.front()]) q.push_front(v);
                else q.pb(v);
                mark[v]=1;
            }
        }
    }
}