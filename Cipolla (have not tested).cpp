ll qp(ll a,ll k)
{
    ll res=1;
    while(k)
    {
        if(k&1) res=res*a%mod;
        a=a*a%mod;
        k>>=1;
    }
    return res;
}

int qp(pii a,int w,ll k)
{
    pii res(1,0);
    auto mul = [&](pii &a,pii &b) {
        pii ans;
        ans.FI = (1ll*a.FI*b.FI + 1ll*a.SE*b.SE%mod*w) % mod;
        ans.SE = (1ll*a.FI*b.SE + 1ll*a.SE*b.FI) % mod;
        return ans;
    };
    while(k)
    {
        if(k&1) res=mul(res,a);
        a=mul(a,a);
        k>>=1;
    }
    return res.FI;
}
int Cipolla(int n) // 0 <= n < mod.
{
    if(n==0) return 0;
    auto check = [](int n) {return qp(n,(mod-1)/2)!=mod-1;};
    if(check(n)==0) return -1;
    if(mod == 2) return n;
    srand(time(NULL));
    while(1)
    {
        int a = myrand(0,mod-1);
        int w = (1ll*a*a - n + mod) % mod;
        if(check(w)==0) return qp({a,1},w,(mod+1)/2);
    }
}