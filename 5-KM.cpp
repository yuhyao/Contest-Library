#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define pb push_back
#define mp make_pair
#define FI first
#define SE second
#define maxn 2000
#define mod 1000000007
#define inf 0x3f3f3f3f
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef double db;

struct KM
{
    int w[maxn+5][maxn+5],x[maxn+5],y[maxn+5];
    int prev_x[maxn+5],prev_y[maxn+5],link[maxn+5],slack[maxn+5],par[maxn+5];
    int N;
    void adjust(int v)
    {
        link[v]=prev_y[v];
        if(prev_x[link[v]]!=-2) adjust(prev_x[link[v]]);
    }
    bool find(int v)
    {
        rep(i,1,N) if(prev_y[i]==-1)
        {
            int t=x[v]+y[i]-w[v][i];
            if(slack[i]>t) slack[i]=t,par[i]=v;
            if(t==0)
            {
                prev_y[i]=v;
                if(link[i]==-1)
                {
                    adjust(i);
                    return 1;
                }
                if(prev_x[link[i]]!=-1) continue; //necessary?
                prev_x[link[i]]=i;
                if(find(link[i])) return 1;
            }
        }
        return 0;
    }
    int solve()
    {
        rep(i,1,N)
        {
            x[i]=-inf;
            rep(j,1,N) x[i]=max(x[i],w[i][j]);
        }
        rep(i,1,N) y[i]=0,link[i]=-1;
        rep(i,1,N)
        {
            rep(j,1,N) prev_x[j]=prev_y[j]=-1,slack[j]=inf;
            prev_x[i]=-2;
            if(find(i)) continue;
            bool flag=0;
            while(!flag) // at most N times?
            {
                int d=inf;
                rep(j,1,N) if(prev_y[j]==-1) d=min(d,slack[j]);
                rep(j,1,N) if(prev_x[j]!=-1) x[j]-=d;
                rep(j,1,N) if(prev_y[j]!=-1) y[j]+=d; else slack[j]-=d;
                rep(j,1,N) if(prev_y[j]==-1 && slack[j]==0)
                {
                    prev_y[j]=par[j];
                    if(link[j]==-1)
                    {
                        adjust(j); flag=1; break;
                    }
                    prev_x[link[j]]=j;
                    if(find(link[j]))
                    {
                        flag=1;
                        break;
                    }
                }
            }
        }
        int ans=0;
        rep(j,1,N) ans+=w[link[j]][j];
        return ans;
    }
}km;

int xb[maxn+5],yb[maxn+5],xc[maxn+5],yc[maxn+5];
int getd(int x1,int y1,int x2,int y2) {return abs(x1-x2)+abs(y1-y2);}

int main()
{
    int n,m; scanf("%d%d",&n,&m);
    rep(i,1,n) scanf("%d%d",&xb[i],&yb[i]);
    rep(i,1,m) scanf("%d%d",&xc[i],&yc[i]);
    int x0,y0; scanf("%d%d",&x0,&y0);

    km.N=n+m-1;
    rep(i,1,n) rep(j,1,m) km.w[i][j]=-getd(xb[i],yb[i],xc[j],yc[j]);
    rep(i,1,n) rep(j,m+1,m+n-1) km.w[i][j]=-getd(xb[i],yb[i],x0,y0);
    int ans=-km.solve();
    rep(i,1,n) ans+=getd(xb[i],yb[i],x0,y0);
    printf("%d\n",ans);
    return 0;
}
