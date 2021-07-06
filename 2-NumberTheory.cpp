#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define max_fac 1000000
using namespace std;
typedef __int128 LL;
typedef long long ll;
ll inv[max_fac+5];
int gcd(int a,int b)
{
    return (b==0)?a:gcd(b,a%b);
}
int exgcd(int a,int b,int &x,int &y)//保证了|x|<=|b|,|y|<=|a|
{
    if(!b) {x=1;y=0;return a;}
    int G=exgcd(b,a%b,x,y);
    int tmp=x;
    x=y;y=tmp-a/b*y;
    return G;
}
int CRT(int a[],int m[],int n)//中国剩余定理，n为方程组个数
{
    int M=1,res=0;
    rep(i,1,n) M*=m[i];
    rep(i,1,n)
    {
        int Mi=M/m[i],x,y;
        exgcd(Mi,m[i],x,y);
        res=(res+1ll*a[i]*Mi%M*x)%M;
    }
    return (res+M)%M;
}

const int mod=1000000007;
ll inv2=(mod+1)>>1;
// Calculate \sum_{i=0}^n floor((a*i+b)/c).
// Note that n should not be unsigned type.
ll Euclidean(ll a,ll b,ll c,ll n)
{
    if(a>=c || b>=c) return (a/c%mod*(n%mod)%mod*((n+1)%mod)%mod*inv2 + (b/c)%mod*((n+1)%mod) + Euclidean(a%c,b%c,c,n))%mod;
    if(a==0) return b/c%mod*((n+1)%mod)%mod;
    ll m=((LL)a*n+b)/c;
    return ((n%mod)*(m%mod)%mod-Euclidean(c,c-b-1,a,m-1)+mod)%mod;
}

int cal_phi(int x)
{
    int tmp=1;
    for(int i=2;1ll*i*i<=x;i++)
    {
        if(x%i==0) tmp*=i-1,x/=i;
        while(x%i==0) x/=i,tmp*=i;
    }
    if(x>1) tmp*=x-1;
    return tmp;
}
void cal_inv(int mod)
{
    inv[1]=1;
    rep(i,2,min(mod-1,max_fac)) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
}

int main()
{
    return 0;
}
