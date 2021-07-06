#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
using namespace std;
typedef long long ll;

inline ll mul(ll a,ll b,ll c)
{
    ll s=a*b-c*ll((long double)a/c*b+0.5);
    return (s<0)?(s+c):s;
}
ll qp(ll a,ll k,ll mod)
{
    ll res=1;
    while(k)
    {
        if(k&1) res=mul(res,a,mod);
        a=mul(a,a,mod);
        k>>=1;
    }
    return res;
}

bool test(ll x,int a)
{
    if(x==a) return 1;
    if(x%2==0) return 0;
    ll d=x-1;
    while(d%2==0) d>>=1;
    ll r=qp(a,d,x);
    if(r==1) return 1;
    while(d<x-1)
    {
        d<<=1;
        if(r==x-1) return 1;
        r=mul(r,r,x);
    }
    return 0;
}

bool miller(ll x)
{
    if(x==2) return 1;
    vi b({2,3,5,7,11,13});
    for(auto p: b) if(test(x,p)==0) return 0;
    return 1;
}

ll pollard(ll n)
{
    if(n%2==0) return 2;
    // using x^2+1 as random choice of x and y.
    auto f = [&](ll x) {ll t=(mul(x,x,n)+1)%n; return t;}; // f(x) = x^2 + 1
    for(int i=2; ;i++)
    {
        ll x=i,y=f(x),g;
        while((g=__gcd(y-x+n,n))==1) x=f(x),y=f(f(y));
        if(g!=n) return g;
    }
}

set<ll> w;

void factor(ll n)
{
    if(n==1) return;
    if(miller(n)) w.insert(n);
    else
    {
        ll x=pollard(n);
        factor(x); factor(n/x);
    }
}