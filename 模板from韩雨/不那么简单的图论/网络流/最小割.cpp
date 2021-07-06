#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int inf=1000000000;
const int maxn=1000,maxm=50000;

struct edge
{
    int to,f,nt;
};

int n,m,src,sink;
int f[maxn+5][maxn+5];
int cup[maxn+5][maxn+5];
int head[maxn+10];
int tot;
edge ed[maxm*2+10];


void addedge(int u,int v,int c)
{
    ed[++tot].to=v;ed[tot].f=c;ed[tot].nt=head[u];head[u]=tot;
    cup[u][v]=c;f[u][v]=0;
    ed[++tot].to=u;ed[tot].f=0;ed[tot].nt=head[v];head[v]=tot;
    cup[v][u]=c;f[v][u]=inf;
}

void init()
{
    memset(f,0,sizeof(f));
    memset(cup,0,sizeof(cup));
    memset(ed,0,sizeof(ed));
    memset(head,0,sizeof(head));
    src=1;sink=n; 
    tot=1;
    //读入，建边 MARK 
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
                f[u][ed[i].to]+=dd;
                f[ed[i].to][u]-=dd;
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

void min_cut()
{
    bool v[maxn+5];
    memset(v,false,sizeof(v));
    queue<int> que;
    que.push(src);
    v[src]=true;
    while (!que.empty()){
        int x=que.front();que.pop();
        for (int i=1;i<=sink;++i){
            if (f[x][i]<cup[x][i] && !v[i]){
                v[i]=true;
                que.push(i);
            }
        }
    }
    for (int i=0;i<=sink;++i) if (v[i])
        for (int j=0;j<=sink;++j) if (!v[j] && f[i][j]==cup[i][j] && cup[i][j]>0){ //不考虑0容量边 
            //添加答案 MARK 
    }    

}

int main()
{
    cin>>n>>m;
    init();
    maxflow();
    min_cut();
}
