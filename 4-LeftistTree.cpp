#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 200000
using namespace std;
struct leftistTree
{
    int l,r,v,d;
}t[maxn+5];
int num[maxn+5],rt[maxn+5];
int getnum(int now)
{
    if(num[now]==now) return now;
    return num[now]=getnum(num[now]);
}
int merge(int x,int y)
{
    if(!x || !y) return x|y;
    if(t[x].v<t[y].v) swap(x,y);
    t[x].r=merge(y,t[x].r);
    if(t[t[x].l].d<t[t[x].r].d) swap(t[x].l,t[x].r);
    t[x].d=t[t[x].r].d+1;
    return x;
}
int pop(int x)
{
    x=rt[getnum(x)];
    int lc=t[x].l,rc=t[x].r;
    t[x].l=t[x].r=t[x].v=t[x].d=0;
    return rt[getnum(lc)]=merge(lc,rc);
}
int top(int x)
{
    return t[rt[getnum(x)]].v;
}
int main()
{
    return 0;
}
