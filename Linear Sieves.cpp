struct LinearSieve
{
    vi prime;
    bool np[maxn+5];
    int d[maxn+5]={0,0},facnum[maxn+5]={1,1},phi[maxn+5]={0,1},mu[maxn+5]={0,1};
    void init(int n)
    {
        rep(i,2,n)
        {
            if(np[i]==0)
            {
                prime.pb(i);
                d[i]=1;
                facnum[i]=2;
                phi[i]=i-1;
                mu[i]=-1;
            }
            for(auto p: prime)
            {
                ll v=1ll*i*p;
                if(v>n) break;
                np[v]=1;
                if(i%p==0)
                {
                    d[v]=d[i]+1;
                    facnum[v]=facnum[i]/(d[i]+1)*(d[v]+1);
                    phi[v]=phi[i]*p;
                    mu[v]=0;
                    break;
                }
                d[v]=1;
                facnum[v]=facnum[i]*2;
                phi[v]=phi[i]*(p-1);
                mu[v]=-mu[i];
            }
        }
    }
	int calphi(int x)
    {
        int tmp=x;
        for(auto p: prime) if(tmp%p==0)
        {
            x=x/p*(p-1);
            while(tmp%p==0) tmp/=p;
        }
        if(tmp>1) x=x/tmp*(tmp-1);
        return x;
    }
}sieve;