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

// length of array a shoule be some power of 2.
void fwt(vi &a) // this is for fwt_OR.
{
    int N=a.size();
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p) rep(k,0,i-1) chadd(a[i+j+k],a[j+k]);
        // for fwt_AND, change to -> chadd(a[j+k],a[i+j+k]);
}
void ifwt(vi& a) // this is for fwt_OR.
{
    int N=a.size();
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p) rep(k,0,i-1) chsub(a[i+j+k],a[j+k]);
        // for fwt_AND, change to -> chsub(a[j+k],a[i+j+k]);
}

inline int Madd(int x,int y) {return x+y<mod?x+y:x+y-mod;}
inline int Msub(int x,int y) {return x-y<0?x-y+mod:x-y;}

void fwt_xor(vi &a,int opt)
{
    int N=a.size();
    for(int i=1;i<N;i<<=1)
        for(int p=i<<1,j=0;j<N;j+=p)
            rep(k,0,i-1)
            {
                int X=a[j+k],Y=a[i+j+k];
                a[j+k]=Madd(X,Y); 
                a[i+j+k]=Msub(X,Y);
            }

    if(opt==-1) 
    {
        int inv=qp(N,mod-2);
        for(auto &x: a) x=1ll*x*inv%mod;
    }
}
int calFWTxor(vi &a,int id)
{
    int N=a.size();
    int res=0;
    rep(k,0,N-1) res=(res+1ll*(__builtin_popcount(k&id)&1?mod-1:1)*a[k])%mod;
    return res;
}