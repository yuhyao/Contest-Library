#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define pb push_back
#define inf 0x3f3f3f3f
using namespace std;

typedef int flow_t;
typedef long long cost_t;
const flow_t MF = inf;
const cost_t MC = 1ll<<60;

struct E {int u,v; flow_t c; cost_t w;};
//Clear when initializing.
vector<E> e;
vi to[maxn+5];

int src,sink;
 
void add(int u,int v,flow_t c,cost_t w)
{
    to[u].pb(e.size()); e.pb(E{u,v,c,w});
    to[v].pb(e.size()); e.pb(E{v,u,0,-w});
}

pair<cost_t,flow_t> costflow(int n)
{
    vector<cost_t> dis(n+1);
    vi pre(n+1);
    vector<bool> mark(n+1);

    deque<int> q;
    cost_t cost=0; flow_t flow=0;
    while(1)
    {
        rep(i,1,n) dis[i]=MC;
        rep(i,1,n) pre[i]=-1;
        rep(i,1,n) mark[i]=0;
        q.pb(src);
        dis[src]=0; mark[src]=1;
        
        while(q.size())
        {
            int now=q.front(); q.pop_front(); mark[now]=0;
            for(auto i: to[now])
            {
                int v=e[i].v;
                if(dis[v]>dis[now]+e[i].w && e[i].c>0)
                {
                    dis[v]=dis[now]+e[i].w;
                    pre[v]=i;
                    if(!mark[v])
                    {
                        if(!q.empty() && dis[v]>=dis[q.front()]) q.pb(v);
                        else q.push_front(v);
                        mark[v]=1;
                    }
                }
            }
        }
        if(dis[sink]==MC) break;
        flow_t mf=MF;
        for(int i=pre[sink];~i;i=pre[e[i].u]) mf=min(mf,e[i].c);
        for(int i=pre[sink];~i;i=pre[e[i].u]) e[i].c-=mf,e[i^1].c+=mf;
        flow+=mf;
        cost+=mf*dis[sink];
    }
    return {cost,flow};
}