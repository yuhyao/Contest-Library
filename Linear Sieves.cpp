struct LinearSieve
{
    vi prime;
    int minp[maxn+5];
    array<int,maxn+5> d,facnum,phi,mu;
    void init(int n)
    {
        facnum[0]=facnum[1]=phi[1]=mu[1]=1;
        prime.clear();
        rep(i,2,n)
        {
            if(minp[i]==0)
            {
                prime.pb(i);
                minp[i]=i;
                d[i]=1;
                facnum[i]=2;
                phi[i]=i-1;
                mu[i]=-1;
            }
            for(auto p: prime)
            {
                ll v=1ll*i*p;
                if(v>n) break;
                minp[v]=p;
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