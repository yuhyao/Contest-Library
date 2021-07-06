#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define maxn 250000
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
vector<pii> e[maxn+5];
vector<int> ve[maxn+5],vec;
int dfn[maxn+5],tot,anc[maxn+5][20],dep[maxn+5],md[maxn+5];
int ex[maxn+5];
int a[maxn+5],sta[maxn+5],top;
void dfs(int now,int fa)
{
    dfn[now]=++tot;
    for(auto it: e[now])
    {
        int v=it.first,w=it.second;
        if(v==fa) continue;
        dep[v]=dep[now]+1;
        md[v]=min(md[now],w);
        anc[v][0]=now;
        dfs(v,now);
    }
}
int swim(int x,int h)
{
    for(int i=0;h;i++,h>>=1) if(h&1) x=anc[x][i];
    return x;
}
int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    x=swim(x,dep[x]-dep[y]);
    if(x==y) return x;
    per(i,0,18)
    {
        if(anc[x][i]==anc[y][i]) continue;
        x=anc[x][i];y=anc[y][i];
    }
    return anc[x][0];
}
bool cmp(int x,int y) {return dfn[x]<dfn[y];}

ll caldp(int now)
{
    if(ex[now]) return md[now];
    ll ret=0;
    for(auto v: ve[now]) ret+=caldp(v);
    if(now!=1) ret=min(ret,(ll)md[now]);
    return ret;
}

int main()
{
    int n,m;
    scanf("%d",&n);
    rep(i,1,n-1)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        e[x].pb(mp(y,z));
        e[y].pb(mp(x,z));
    }
    md[1]=0x3f3f3f3f;
    dfs(1,0);
    rep(i,1,18) rep(j,1,n) anc[j][i]=anc[anc[j][i-1]][i-1];
    scanf("%d",&m);
    while(m--)
    {
        for(auto v: vec) ve[v].clear();
        vec.clear();
        int k;
        scanf("%d",&k);
        rep(i,1,k) scanf("%d",&a[i]);
        sort(a+1,a+k+1,cmp);
        rep(i,1,k) ex[a[i]]=1;
        top=0;
        rep(i,1,k)
        {
            if(top==0) {sta[++top]=a[i];continue;}
            int _lca=lca(a[i],sta[top]);
            while(top>1 && dep[_lca]<=dep[sta[top-1]]) vec.pb(sta[top]),ve[sta[top-1]].pb(sta[top]),top--;
            if(dep[_lca]<dep[sta[top]]) vec.pb(sta[top]),ve[_lca].pb(sta[top]),top--;
            if(top==0 || _lca!=sta[top]) sta[++top]=_lca;
            sta[++top]=a[i];
        }
        while(top>1) vec.pb(sta[top]),ve[sta[top-1]].pb(sta[top]),top--;
        vec.pb(sta[top]);

        printf("%lld\n",caldp(sta[top]));
        rep(i,1,k) ex[a[i]]=0;
    }
    return 0;
}
