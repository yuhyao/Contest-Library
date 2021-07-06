#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn (1<<19)
#define mod 1000000007
using namespace std;
typedef long long ll;
int inv2=(mod+1)>>1;
int N;//should be power of 2.
void FWT_or(int *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            rep(k,0,i-1)
                if(opt==1) a[i+j+k]=(a[j+k]+a[i+j+k])%mod;
                else a[i+j+k]=(a[i+j+k]+mod-a[j+k])%mod;
}
void FWT_and(int *a,int opt)
{
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            rep(k,0,i-1)
                if(opt==1) a[j+k]=(a[j+k]+a[i+j+k])%mod;
                else a[j+k]=(a[j+k]+mod-a[i+j+k])%mod;
}
void FWT_xor(int *a,int opt)
{
    ll fac=(opt==-1)?inv2:1;
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            rep(k,0,i-1)
            {
                int X=a[j+k],Y=a[i+j+k];
                a[j+k]=fac*(X+Y)%mod;a[i+j+k]=fac*(X+mod-Y)%mod;
            }
}
int calFWTxor(int *a,int id)
{
    int sgn[2]={1,mod-1};
    int tot=0;
    rep(k,0,N-1) tot=(tot+1ll*sgn[__builtin_popcount(k&id)&1]*a[k])%mod;
    return tot;
}
int main()
{
    rep(i,1,maxn-1) bitcnt[i]=bitcnt[i>>1]+(i&1);
    return 0;
}
