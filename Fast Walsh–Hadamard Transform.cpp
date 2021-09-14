#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn (1<<19)
#define mod 1000000007
using namespace std;
typedef long long ll;

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

inline void chadd(int &x,int y) {x+=y; if(x>=mod) x-=mod;}
inline void chsub(int &x,int y) {x-=y; if(x<0) x+=mod;}

void fwt_or(vi &a,int opt)
{
    int N=a.size();
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            rep(k,0,i-1)
                if(opt==1) chadd(a[i+j+k],a[j+k]);
                else chsub(a[i+j+k],a[j+k]);
}

void fwt_and(vi &a,int opt)
{
    int N=a.size();
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            rep(k,0,i-1)
                if(opt==1) chadd(a[j+k],a[i+j+k]);
                else chsub(a[j+k],a[i+j+k]);
}

inline int Madd(int x,int y) {return x+y<mod?x+y:x+y-mod;}
inline int Msub(int x,int y) {return x-y<0?x-y+mod:x-y;}

void fwt_xor(vi &a,int opt)
{
    int N=a.size();
    ll fac=(opt==-1)?inv2:1;
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            rep(k,0,i-1)
            {
                int X=a[j+k],Y=a[i+j+k];
                a[j+k]=Madd(X,Y); 
				a[i+j+k]=Msub(X,Y)%mod;
            }
            
    if(opt==-1) 
    {
        int inv=qp(N,mod-2);
        for(auto &x: a) x=1ll*x*inv%mod;
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
