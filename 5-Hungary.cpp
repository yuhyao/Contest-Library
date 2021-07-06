#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 300
using namespace std;
int from[maxn+5];
bool used[maxn+5];
int ans,n,m;
vector<int> e[maxn+5];
bool match(int u)
{
    for(auto v: e[u])
    {
        if(!used[v])
        {
            used[v]=1;
            if(from[v]==-1 || match(from[v]))
            {
                from[v]=u;
                return 1;
            }
        }
    }
    return 0;
}
int hungary()
{
    int tot=0;
    memset(from,-1,sizeof from);
    rep(i,1,n)
    {
        memset(used,0,sizeof used);
        if(match(i)) tot++;
    }
    return tot;
}
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        rep(i,1,n) e[i].clear();
        rep(i,1,m)
        {
            //u为左侧端点, v为右侧端点. 均从1开始编号.
            int u,v;
            scanf("%d%d",&u,&v);
            e[u].push_back(v);
        }
        printf("%d\n",hungary());
    }
    return 0;
}
