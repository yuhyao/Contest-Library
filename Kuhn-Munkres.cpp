// Maximum weight perfect matching. Time Complexity: O(n^3).
// indices start from 1.
// inf can only be 0x3f3f3f3f but not 1ll<<60.
struct KM
{
    int n;
    ll w[maxn+5][maxn+5],x[maxn+5],y[maxn+5],slack[maxn+5];
    int prev_x[maxn+5],prev_y[maxn+5],link[maxn+5],par[maxn+5];
    void init(int _n)
    {
        n=_n; rep(i,1,n) rep(j,1,n) w[i][j]=-inf;
    }
    void adjust(int v)
    {
        link[v]=prev_y[v];
        if(prev_x[link[v]]!=-2) adjust(prev_x[link[v]]);
    }
    bool find(int v)
    {
        rep(i,1,n) if(prev_y[i]==-1)
        {
            ll t=x[v]+y[i]-w[v][i];
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
    ll work()
    {
        rep(i,1,n)
        {
            x[i]=-1ll<<60;
            rep(j,1,n) x[i]=max(x[i],w[i][j]);
        }
        rep(i,1,n) y[i]=0,link[i]=-1;
        rep(i,1,n)
        {
            rep(j,1,n) prev_x[j]=prev_y[j]=-1,slack[j]=1ll<<60;
            prev_x[i]=-2;
            if(find(i)) continue;
            bool flag=0;
            while(!flag) // at most N times?
            {
                ll d=1ll<<60;
                rep(j,1,n) if(prev_y[j]==-1) d=min(d,slack[j]);
                rep(j,1,n) if(prev_x[j]!=-1) x[j]-=d;
                rep(j,1,n) if(prev_y[j]!=-1) y[j]+=d; else slack[j]-=d;
                rep(j,1,n) if(prev_y[j]==-1 && slack[j]==0)
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
        ll ans=0;
        rep(j,1,n) ans+=w[link[j]][j];
        return ans;
    }
}km;