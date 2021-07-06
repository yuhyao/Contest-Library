#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
using namespace std;
typedef long long ll;
int prime[10]={0,2,3,5,7,11,13};
inline ll mul(ll a,ll b,ll mod)
{
    ll s=a*b-mod*ll((long double)a/mod*b+0.5);
    return (s<0)?(s+mod):s;
}
ll qp(ll a,ll k,ll mod)
{
    ll ret=1;
    while(k)
    {
        if(k&1) ret=mul(ret,a,mod);
        a=mul(a,a,mod);
        k>>=1;
    }
    return ret;
}
bool test(ll x,int a)
{
    if(x==a) return 1;
    if(x%2==0) return 0;
    ll d=x-1;
    while(d%2==0) d>>=1;
    ll tmp=qp(a,d,x);
    if(tmp==1) return 1;
    while(d<x-1)
    {
        d<<=1;
        if(tmp==x-1) return 1;
        tmp=mul(tmp,tmp,x);
    }
    return 0;
}
bool miller(ll x)//判断x是否是素数。
{
    if(x<2) return 0;
    if(x==2) return 1;
    //选取底数进行测试，int以内2、3、5、7作为底数足够了。
    rep(i,1,6) if(!test(x,prime[i])) return 0;
    return 1;
}
int main()
{
    ll x;
    while(~scanf("%lld",&x)) printf("%d\n",miller(x));
    return 0;
}
