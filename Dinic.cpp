#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 200
#define inf 0x3f3f3f3f
using namespace std;

typedef int flow_t;
const flow_t MF = inf;

struct E
{
    int u,v; flow_t c;
    E(){}
    E(int u,int v,flow_t c):u(u),v(v),c(c){}
};
//Clear when initializing.
vector<E> e;
vi to[maxn+5];

int d[maxn+5],src,sink,cur[maxn+5];

void add(int u,int v,flow_t c)
{
    to[u].pb(e.size()); e.pb(E(u,v,c));
    to[v].pb(e.size()); e.pb(E(v,u,0));
}
int bfs(int n)
{
    rep(i,1,n) d[i]=-1;
    queue<int> q;
    q.push(src); d[src]=0;
    while(q.size())
    {
        int now=q.front(); q.pop();
        for(auto i: to[now])
        {
            int v=e[i].v;
            if(e[i].c>0 && d[v]==-1)
            {
                d[v]=d[now]+1;
                q.push(v);
            }
        }
    }
    return d[sink]!=-1;
}
flow_t dfs(int now,flow_t f)
{
    if(now==sink) return f;
    flow_t r=0;
    int l=to[now].size();
    for(int &id=cur[now];id<l;id++)
    {
        int i=to[now][id],v=e[i].v;
        if(e[i].c>0 && d[v]==d[now]+1)
        {
            flow_t tmp=min(f-r,e[i].c);
            flow_t x=dfs(v,tmp);
            r+=x;
            e[i].c-=x;
            e[i^1].c+=x;
        }
        if(r==f) break;
    }
    return r;
}
flow_t maxflow(int n)
{
    flow_t flow=0;
    while(bfs(n))
    {
        rep(i,1,n) cur[i]=0;
        flow+=dfs(src,MF);
    }
    return flow;
}

int main()
{
    return 0;
}
