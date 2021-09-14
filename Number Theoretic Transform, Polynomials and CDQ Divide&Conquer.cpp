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
    Transform(){init();}

    void NTT(vi &a,int is_inv) // is_inv == 1 -> iDFT.
    {
        rep(i,1,n2-1) if(r[i]>i) swap(a[i],a[r[i]]);
        rep(t,0,len-1)
        {
            int step=1<<t,step2=1<<(t+1);
            vi w(step); w[0]=1;
            rep(i,1,step-1) w[i]=1ll*w[i-1]*wn[t+1][is_inv]%mod;
            for(int i=0;i<n2;i+=step2)
            {
                rep(j,0,step-1)
                {
                    int tmp=1ll*w[j]*a[i+j+step]%mod;
                    a[i+j+step]=Msub(a[i+j],tmp);
                    a[i+j]=Madd(a[i+j],tmp);
                }
            }
        }
        if(is_inv==1) 
        {
            ll inv=qp(n2,mod-2);
            rep(i,0,n2-1) a[i]=a[i]*inv%mod;
        }
    }

    void pre(int n) // set n2, r;
    {
        len=0;
        for(n2=1;n2<n;n2<<=1) len++;
        r.resize(n2);
        rep(i,1,n2-1) r[i]=(r[i>>1]>>1)|((i&1)<<(len-1));
    }

    vi conv(vi A,vi B)
    {
        int n=A.size()+B.size()-1;
        pre(n);
    
        A.resize(n2,0);
        B.resize(n2,0);
        NTT(A,0);
        NTT(B,0);
        rep(i,0,n2-1) A[i]=1ll*A[i]*B[i]%mod;
        NTT(A,1);
        A.resize(n);
        return A;
    }
    vi inverse(vi f) // view f as a polynimial and deg(f) = n-1, then return f^{-1} (mod x^n)
    {
        if(f.size()==1) return vi{(int)qp(f[0],mod-2)};

        int n=f.size();
        int m=(n+1)>>1;
        vi g=inverse(vi(f.begin(),f.begin()+m));
        pre(n*2-1);
        
        f.resize(n2,0);
        g.resize(n2,0);
        NTT(f,0);
        NTT(g,0);
        rep(i,0,n2-1) g[i]=(2ll-1ll*f[i]*g[i]%mod+mod)%mod*g[i]%mod;
        NTT(g,1);
        g.resize(n);
        return g;
	}
}ntt;

typedef vector<int> poly;

int eval(const poly &a,int x)
{
	int ans=0,pw=1;
	for(auto c: a)
    {
		ans=(ans+1ll*c*pw)%mod;
		pw=1ll*pw*x;
	}
	return ans;
}

poly& operator +=(poly &a,const poly &b)
{
	if(a.size()<b.size()) a.resize(b.size(),0);
	rep(i,0,(int)b.size()-1) a[i]=Madd(a[i],b[i]);
	return a;
} 
poly operator +(const poly &a,const poly &b) {auto c=a; return c+=b;}
poly& operator -=(poly &a,const poly &b)
{
	if(a.size()<b.size()) a.resize(b.size(),0);
	rep(i,0,(int)b.size()-1) a[i]=Msub(a[i],b[i]);
	return a;
} 
poly operator -(const poly &a,const poly &b) {auto c=a; return c-=b;}
poly& operator *=(poly &a,const poly &b)
{
    if(min(a.size(),b.size())<128)
    {
        vi c=a;
        a.assign(a.size()+b.size()-1,0);
        rep(i,0,(int)c.size()-1) rep(j,0,(int)b.size()-1) a[i+j]=(a[i+j]+1ll*c[i]*b[j])%mod;
    } 
    else a=ntt.conv(a,b);
	return a;
}

poly operator *(const poly &a,const poly &b) {auto c=a; return c*=b;}
poly& operator /=(poly &a,const poly &b)
{
    int n=a.size(),m=b.size();
    if(n<m) a.clear();
    else
    {
        auto c=b;
        reverse(a.begin(),a.end());
        reverse(c.begin(),c.end());
        c.resize(n-m+1);
        a*=ntt.inverse(c);
        a.erase(a.begin()+n-m+1,a.end());
        reverse(a.begin(),a.end());
    }
    return a;
}
poly operator /(const poly &a,const poly &b) {auto c=a; return c/=b;}
poly& operator %=(poly &a,const poly &b)
{
    int n=a.size(),m=b.size();
    if(n>=m)
    {
        auto c=a/b*b;
        a.resize(m-1);
        rep(i,0,m-2) a[i]=Msub(a[i],c[i]);
    }
    return a;
}
poly operator %(const poly &a,const poly &b) {auto c=a; return c%=b;}

poly mulxk(const poly &a,int k) // return a * x^k.
{
    poly b=a;
    b.insert(b.begin(),k,0);
    return b;
}
poly modxk(const poly &a,int k) // reutrn a % x^k
{
    chmin(k,(int)a.size());
    return poly(a.begin(),a.begin()+k);
}
poly divxk(const poly &a,int k) // reutrn a / x^k
{
    if((int)a.size()<=k) return poly{};    
    return poly(a.begin()+k,a.end());
}

// return the coefficient of x^k in P/Q, where the constant term in Q should be 1.
int kth_coeff(poly P,poly Q,int k) 
{
    int n=P.size()-1,m=Q.size()-1;
    auto A=Q; A.resize(n+m+1);
    A=P*ntt.inverse(A); A.resize(n+m+1);
    if(k<=n+m) return A[k];
    reverse(Q.begin(),Q.end());
    auto qp=[](poly a,ll k,poly Q) {
        poly res{1};
        while(k)
        {
            if(k&1) res=res*a%Q;
            a=a*a%Q;
            k>>=1;
        }
        return res;
    };
    k-=n;
    auto res=qp(poly{0,1},k,Q);
    int ans=0;
    rep(i,0,m-1) ans=(ans+1ll*A[i+n]*res[i])%mod;
    return ans;
}

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