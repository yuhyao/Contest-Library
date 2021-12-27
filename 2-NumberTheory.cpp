// input: a>=0, b>=0
// guarantees |x|<=b, |y|<=a if (a>0 or b>0).
template<class T> T exgcd(T a,T b,T &x,T &y) 
{
    if(!b) {x=1;y=0;return a;}
    T G=exgcd(b,a%b,x,y);
    T tmp=x;
    x=y;y=tmp-a/b*y;
    return G;
}
// input: m_0, ..., m_{n-1} should be pairwise coprime.
// output: solution in [0，M)
// be careful if you need __int128 in multiplication.
ll CRT(vector<ll> a,vector<ll> m)
{
    ll M=1,res=0;
    for(auto x: m) M *= x;
    rep(i,0,sz(a)-1)
    {
        ll Mi=M/m[i],x,y;
        exgcd(Mi,m[i],x,y);
        res = (res + a[i] % m[i] * Mi % M * x) % M;
    }
    return (res + M) % M;
}

// Calculate \sum_{i=0}^n floor((a*i+b)/c).
// Note that n should not be unsigned type.
const int mod=1000000007;
ll inv2=(mod+1)>>1;
ll Euclidean(ll a,ll b,ll c,ll n)
{
    if(a>=c || b>=c) return (a/c%mod*(n%mod)%mod*((n+1)%mod)%mod*inv2 + (b/c)%mod*((n+1)%mod) + Euclidean(a%c,b%c,c,n))%mod;
    if(a==0) return b/c%mod*((n+1)%mod)%mod;
    ll m=((LL)a*n+b)/c;
    return ((n%mod)*(m%mod)%mod-Euclidean(c,c-b-1,a,m-1)+mod)%mod;
}

ll cal_phi(ll x)
{
    ll tmp=1;
    for(ll i=2;i*i<=x;i++)
    {
        if(x%i==0) tmp*=i-1,x/=i;
        while(x%i==0) x/=i,tmp*=i;
    }
    if(x>1) tmp*=x-1;
    return tmp;
}
ll inv[maxn+5];
void cal_inv(int mod,int n) // should have n < mod.
{
    inv[1]=1;
    rep(i,2,n) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
}