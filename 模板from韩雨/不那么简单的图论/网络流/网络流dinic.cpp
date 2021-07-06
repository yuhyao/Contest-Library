#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int inf=1000000000;
const int maxn=400,maxm=4000;

struct edge
{
    int to,f,nt;
};

int n,m,src,sink,ans,u,v,c;
int head[maxn+10];
int tot;
edge ed[maxm*2+10];
void addedge(int u,int v,int c)
{
    ed[++tot].to=v;ed[tot].f=c;ed[tot].nt=head[u];head[u]=tot;
    ed[++tot].to=u;ed[tot].f=0;ed[tot].nt=head[v];head[v]=tot;
}

void init()
{
    memset(ed,0,sizeof(ed));
    memset(head,0,sizeof(head));
    src=1;sink=n;
    for (int i=1;i<=m;++i){
        cin>>u>>v>>c;
        addedge(u,v,c);
    }
    tot=1;
}

queue<int> que;
bool vis[maxn+10];
int dis[maxn+10];

void bfs()
{
    memset(dis,0,sizeof(dis));
    while (!que.empty()) que.pop();
    vis[src]=true;
    que.push(src);
    while (!que.empty()){
        int u=que.front();
        que.pop();
        for (int i=head[u];i;i=ed[i].nt)
            if (ed[i].f && !vis[ed[i].to]){
                que.push(ed[i].to);
                dis[ed[i].to]=dis[u]+1;
                vis[ed[i].to]=true;
            }
    }
}

int dfs(int u,int delta)
{
    if (u==sink){
        return delta;
    }    else {
        int ret=0;
        for (int i=head[u];delta && i;i=ed[i].nt)
            if (ed[i].f && dis[ed[i].to]==dis[u]+1){
                int dd=dfs(ed[i].to,min(ed[i].f,delta));
                ed[i].f-=dd;
                ed[i^1].f+=dd;
                delta-=dd;
                ret+=dd;
            }
        return ret;
    }
}

int maxflow()
{
    int ret=0;
    while (true){
        memset(vis,false,sizeof(vis));
        bfs();
        if (!vis[sink]) return ret;
        ret+=dfs(src,inf);
    }
    return ret;
}

int main()
{
    while (cin>>m>>n){
        init();
        ans=maxflow();
        cout<<ans<<endl;
    }
}
