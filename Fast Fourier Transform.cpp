typedef complex<double> cp;
const double pi=acos(-1.0);

int n2;
vi r;
void FFT(vector<cp> &a,int opt)
{
    rep(i,1,n2-1) if(r[i]>i) swap(a[i],a[r[i]]);
    vector<cp> w;
    for(int step=1;step<n2;step<<=1)
    {
        w.clear();
        rep(j,0,step-1) 
        {
            cp x; db theta=pi*j/step*opt;
            x.real(cos(theta)); x.imag(sin(theta));
            w.pb(x);
        }
        for(int step2=step<<1,i=0;i<n2;i+=step2)
        {
            rep(j,0,step-1)
            {
                cp even=a[i+j];
                cp tmp=w[j]*a[i+j+step];
                a[i+j]=even+tmp;
                a[i+j+step]=even-tmp;
            }
        }
    }
}
vi conv(vi &a,vi &b)
{
    int n=a.size()+b.size()-1;
    
    int len=0;
    for(n2=1;n2<n;n2<<=1) len++;
    r.resize(n2);
    rep(i,1,n2-1) r[i]=(r[i>>1]>>1)|((i&1)<<(len-1));
    
    vector<cp> x(n2,0),y(n2,0);
    rep(i,0,(int)a.size()-1) x[i]=a[i];
    rep(i,0,(int)b.size()-1) y[i]=b[i];
    
    FFT(x,1);
    FFT(y,1);
    rep(i,0,n2-1) x[i]=x[i]*y[i];
    FFT(x,-1);
    
    vi c(n2,0);
    rep(i,0,n2-1) c[i]=x[i].real()/n2+0.5;
    c.resize(n);
    return c;
}

const int mod=1000000007;
void work(vector<cp> &a,vector<cp> &b,vi &ans,int w)
{
    vector<cp> tmp(n2,0);
    rep(i,0,n2-1) tmp[i]=a[i]*b[i];
    FFT(tmp,-1);
    rep(i,0,n2-1) ans[i]=(ans[i]+(ll)(tmp[i].real()/n2+0.5)%mod*w)%mod;
}
vi conv_MOD(vi &a,vi &b)
{
    int M=sqrt(mod)+0.5;
    int n=a.size()+b.size()-1;

    int len=0;
    for(n2=1;n2<n;n2<<=1) len++;
    r.resize(n2);
    rep(i,1,n2-1) r[i]=(r[i>>1]>>1)|((i&1)<<(len-1));

    vector<cp> A(n2,0),B(n2,0),C(n2,0),D(n2,0);
    rep(i,0,(int)a.size()-1) A[i]=a[i]/M,B[i]=a[i]%M;
    rep(i,0,(int)b.size()-1) C[i]=b[i]/M,D[i]=b[i]%M;

    FFT(A,1); FFT(B,1); FFT(C,1); FFT(D,1);
    vi c(n2,0);
    work(A,C,c,1ll*M*M%mod);
    work(B,D,c,1);
    work(A,D,c,M);
    work(B,C,c,M);
    c.resize(n);
    return c;
}
