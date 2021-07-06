template<class T> bool chmin(T &a, const T &b) {if(b<a) {a=b; return 1;} return 0;}

int dis[maxn+5];
bool mark[maxn+5];
vector<pii> e[maxn+5];
void spfa(int src)
{
    memset(dis,63,sizeof dis);
    memset(mark,0,sizeof mark);
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
    return;
}