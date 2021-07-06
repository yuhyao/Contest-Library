#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 1000
#define mod 1000000007
using namespace std;
typedef long long ll;
int a[maxn+5];
ll inv[maxn+10],fac[maxn+10],B[maxn+10];
inline ll qp(ll a,int k)
{
    ll ret=1;
    while(k)
    {
        if(k&1) ret=ret*a%mod;
        a=a*a%mod;
        k>>=1;
    }
    return ret;
}
inline ll _inv(ll a)
{
    return qp(a,mod-2);
}
inline ll C(int n,int m)
{
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
inline ll cal(int k,int n)
{
    if(k==0) return n;
    ll mul=1,ret=0;
    rep(i,1,k+1)
    {
        mul=mul*(n+1)%mod;
        ret=(ret+C(k+1,i)*B[k+1-i]%mod*mul)%mod;
    }
    ret=ret*_inv(k+1)%mod;
    return ret;
}
int main()
{
    inv[0]=inv[1]=fac[0]=1;
    rep(i,2,maxn+5) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
    rep(i,1,maxn+5) inv[i]=inv[i]*inv[i-1]%mod;
    rep(i,1,maxn+5) fac[i]=1ll*i*fac[i-1]%mod;

    B[0]=1;
    rep(i,1,maxn)
    {
        rep(j,0,i-1) B[i]=(B[i]+C(i+1,j)*B[j])%mod;
        B[i]=(-B[i]*_inv(i+1)%mod+mod)%mod;
    }

    int n;
    while(~scanf("%d",&n))
    {
        rep(i,1,n) scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        ll ans=0,mul=1;
        rep(i,1,n)
        {
            int k=n+1-i;
            ll tmp=0;
            tmp=(tmp+qp(a[i],k+1)-qp(a[i-1],k)*(a[i-1]+1))%mod;
            tmp=(tmp-(cal(k,a[i]-1)-cal(k,a[i-1])))%mod;
            ans=(ans+tmp*mul)%mod;
            mul=mul*a[i]%mod;
        }
        printf("%lld\n",(ans+mod)%mod);
    }

    return 0;
}
