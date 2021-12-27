ll p[maxn+5];
int np[maxn+5]={1,1},pi[maxn+5];

ll w[maxn*2+5],S[maxn*2+5];
int id1[maxn+5],id2[maxn+5],sq,m;

ll mysqrt(ll n)
{
    ll x=sqrt(n);
    while(x*x<n) x++;
    while(x*x>n) x--;
    return x;
}
void sol(ll n)
{
    sq=mysqrt(n);
    m=pi[sq];
    ll l=1,r;
    int tot=0;
    while(l<=n)
    {
        ll val=n/l;
        r=n/val;
        if(val<=sq) id1[val]=++tot;
        else id2[r]=++tot;
        //下面的S[tot] = sum_i^{val} F(i) - F(1)，这里F(i)是指将i当作质数后F(i)的值，比如令F=miu，那么对所有的i>1，我们认为F[i]均是-1。
        S[tot]=ask(val)-ask(1);
        w[tot]=val;
        l=r+1;
    }
    //zh[n]=F(p[1])+F(p[2])+...+F(p[n])
    rep(i,1,m) rep(j,1,tot)
    {
        if(1ll*p[i]*p[i]>w[j]) break;
        int op=(w[j]/p[i]<=sq)?id1[w[j]/p[i]]:id2[n/(w[j]/p[i])];
        // delta(x) 表示把数都当成质数后，F(i*x)/F(i)。
        S[j]=S[j]-delta(p[i])*(S[op]-zh[i-1]);
    }
    per(i,1,m) rep(j,1,tot)
    {
        if(1ll*p[i]*p[i]>w[j]) break;
        for(ll o=p[i],u=w[j]/p[i];o*p[i]<=uu;o=o*p[i],u=u/p[i])
        {
            op=(u<=sq)?id1[u]:id2[n/u];
            S[j]+=(S[op]-zh[i])*F(o)+F(o*p[i]);
        }
    }
    S[tot+1]=-F(1);//这条语句的存在是因为S中不含F(1)。
    //如有必要，分O(sqrt(n))段计算和。
    rep(i,1,tot)
    {
        int N=n/w[i];
        ans=(ans+(S[i]-S[i+1])*cal(N)%mod+mod)%mod;
    }
}
//zh[n]=F(p[1])+F(p[2])+...+F(p[n])
//sq=mysqrt(n)
//m=pi[sq];
inline ll ask(ll x,int k)
{
    if(x<=1 || p[k]>x) return 0;
    int wz=(x<=sq)?id1[x]:id2[n/x];
    ll ans=S[wz]-zh[k-1];
    for(int i=k;i<=m && 1ll*p[i]*p[i]<=x;i++)
        for(ll l=p[i];l*p[i]<=x;l=l*p[i])
            ans=ans+ask(x/l,i+1)*F(l)+F(p[i]*l);
    return ans;
}
//ans=ask(n,1)+F(1);

int main()
{    
    int p_num=0;
    rep(i,2,maxn)
    {
        if(!np[i]) p[++p_num]=i;
        rep(j,1,p_num)
        {
            ll v=1ll*i*p[j];
            if(v>maxn) break;
            np[v]=1;
            if(i%p[j]==0) break;
        }
    }
    rep(i,1,maxn) pi[i]=pi[i-1]+(1-np[i]);
}
