// Time Complexity of pollard-rho is O(n^{1/4}).
// Time Complexity of factorization is also O(n^{1/4})!
inline ll mul(ll a,ll b,ll c)
{ // using __int128 is a little bit slower，
    ll s=a*b-c*ll((long double)a/c*b+0.5);
    return (s<0)?(s+c):s;
}
ll qp(ll a,ll k,ll mod)
{
    ll res=1;
    for(;k;k>>=1,a=mul(a,a,mod)) if(k&1) res=mul(res,a,mod);
    return res;
}

bool test(ll n,int a)
{
    if(n==a) return 1;
    if(n%2==0) return 0;
    ll d = (n-1) >> __builtin_ctzll(n-1);
    ll r = qp(a,d,n);
    while(d<n-1 && r!=1 && r!=n-1) d<<=1, r=mul(r,r,n);
    return r==n-1 || d%2;
}
bool miller(ll n)
{
    if(n==2) return 1;
    vi b({2,3,5,7,11,13});
    for(auto p: b) if(test(n,p)==0) return 0;
    return 1;
}

mt19937_64 rng(20000902);
ll myrand(ll l,ll r) { return l + rng()%(r-l+1); }
ll pollard(ll n) // return some nontrivial factor of n.
{
    auto f = [&](ll x) { return ((LL)x * x + 1) % n; };
    ll x = 0, y = 0, t = 30, prd = 2;
    while(t++%40 || __gcd(prd, n)==1) 
    {   // speedup: don't take __gcd in each iteration.
        if(x==y) x = myrand(2,n-1), y = f(x);
        ll tmp = mul(prd, abs(x-y), n);
        if(tmp) prd = tmp;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}

void factorization(ll n,vector<ll> &w)
{
    if(n==1) return;
    if(miller(n)) w.pb(n);
    else
    {
        ll x=pollard(n);
        factorization(x,w); factorization(n/x,w);
    }
}