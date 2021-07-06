#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 100000
using namespace std;
int fa[maxn+5],val[maxn+5],n,m,q;
//val[i]为i相对fa[i]的权值
int getfa(int now)
{
    if(fa[now]==now) return now;
    int oldfa=fa[now];
    fa[now]=getfa(oldfa);
    val[now]^=val[oldfa];
    return fa[now];
}
int check(int v,int x,int y)
{
    int xfa=getfa(x),yfa=getfa(y);
    if(xfa!=yfa) return 2;//x和y不连通
    if(v==(val[x]^val[y])) return 1;//x和y值相反
    return 0;//x和y值相同
}
void modify(int v,int x,int y)
{
    int xfa=getfa(x),yfa=getfa(y);
    if(xfa==yfa) return;
    fa[xfa]=yfa;
    val[xfa]=v^val[y]^val[x];
    return;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    rep(i,1,n) fa[i]=i;
    rep(i,1,n) val[i]=0;
    rep(i,1,m)
    {
        int x,y,v;
        scanf("%d%d%d",&x,&y,&v);
        if(check(1,x,y)==2) modify(v,x,y);
    }
    rep(i,1,q)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        int judge=check(1,x,y);
        if(judge==2) printf("Not connected.\n");
        else if(judge==1) printf("They don't have same value.\n");
        else if(judge==0) printf("They have same value.\n");
    }
    return 0;
}
