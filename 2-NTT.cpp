const int mod=998244353;//469762049, 2281701377 are ok.
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

inline int Madd(int x,int y) {return x+y<mod?x+y:x+y-mod;}
inline int Msub(int x,int y) {return x-y<0?x-y+mod:x-y;}

struct Transform
{
    const int g=3;
    int wn[30][2];
    vi r;
    int n2,len;

    void init()
    {
        rep(i,0,20)
        {
            wn[i][0]=qp(g,(mod-1)/(1<<i));
            wn[i][1]=qp(wn[i][0],mod-2);
        }
    }

    void NTT(vi &a,int opt)
    {
        rep(i,1,n2-1) if(r[i]>i) swap(a[i],a[r[i]]);
        rep(t,0,len-1)
        {
            int step=1<<t,step2=1<<(t+1);
            int w=wn[t+1][opt];
            for(int i=0;i<n2;i+=step2)
            {
                ll wj=1;
                rep(j,0,step-1)
                {
                    int tmp=wj*a[i+j+step]%mod;
                    a[i+j+step]=Msub(a[i+j],tmp);
                    a[i+j]=Madd(a[i+j],tmp);
                    wj=wj*w%mod;
                }
            }
        }
        if(opt==1) 
        {
            ll inv=qp(n2,mod-2);
            rep(i,0,n2-1) a[i]=a[i]*inv%mod;
        }
    }

    vi conv(vi A,vi B)
    {
        int n=A.size()+B.size()-1;
    
        len=0;
        for(n2=1;n2<n;n2<<=1) len++;
        r.resize(n2);
        rep(i,1,n2-1) r[i]=(r[i>>1]>>1)|((i&1)<<(len-1));
    
        A.resize(n2,0);
        B.resize(n2,0);
        NTT(A,0);
        NTT(B,0);
        rep(i,0,n2-1) A[i]=1ll*A[i]*B[i]%mod;
        NTT(A,1);
        A.resize(n);
        return A;
    }
}ntt;

// CDQ D&C:
// Solve f(n) = c(n) \sum_{i=1}^{n} g(i)f(n-i), where g is known.
// Initialize f(0);
// Run: CDQ(0,n).
int g[maxn+5],f[maxn+5];
void CDQ(int l,int r)
{
    if(l==r) 
    {
        // We mutiply f(n) by c(n) here. Eg: c(n)=1/n.
        if(l!=0) f[l]=f[l]*inv[l]%mod;
        return;
    }
    int mid=(l+r)>>1,n=r-l+1;
    CDQ(l,mid);
    vi A(n),B(mid-l+1);
    rep(i,0,n-1) A[i]=g[i]%mod;
    rep(i,l,mid) B[i-l]=f[i]%mod;
    vi C=ntt.conv(A,B);
    rep(i,mid+1,r) f[i]=(f[i]+C[i-l]%mod)%mod;
    CDQ(mid+1,r);
}