#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 100000
#define inf (1ll<<60)
using namespace std;
typedef long long ll;
struct P
{
    int x[2];
}p[maxn+5],ori[maxn+5];

int key,dim=2;

bool cmp(P a,P b) {return a.x[key]<b.x[key];}
ll sqr(ll x) {return x*x;}

void build(int l,int r,int dep)
{
    if(l>=r) return;
    int mid=(l+r)>>1;
    key=dep%dim;
    nth_element(p+l,p+mid,p+r+1,cmp);
    build(l,mid-1,dep+1);
    build(mid+1,r,dep+1);
}

P cen;

ll dis(P p)
{
    ll d=0;
    rep(i,0,dim-1) d+=sqr(p.x[i]-cen.x[i]);
    return d?d:inf;
}

ll ask(int l,int r,int depth)
{
    if(l>r) return inf;
    if(l==r) return dis(p[l]);

    int mid=(l+r)>>1;
    int cur=depth%dim;
    ll ret=dis(p[mid]),tmp;
    if(cen.x[cur]<p[mid].x[cur])
    {
        tmp=ask(l,mid-1,depth+1);
        if(tmp>sqr(cen.x[cur]-p[mid].x[cur])) tmp=min(tmp,ask(mid+1,r,depth+1));
    }
    else
    {
        tmp=ask(mid+1,r,depth+1);
        if(tmp>sqr(cen.x[cur]-p[mid].x[cur])) tmp=min(tmp,ask(l,mid-1,depth+1));
    }
    return min(ret,tmp);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n; scanf("%d",&n);
        rep(i,1,n)
        {
            rep(j,0,dim-1) scanf("%d",&p[i].x[j]);
            ori[i]=p[i];
        }
        build(1,n,0);
        rep(i,1,n)
        {
            cen=ori[i];
            printf("%lld\n",ask(1,n,0));
        }
    }
    return 0;
}
