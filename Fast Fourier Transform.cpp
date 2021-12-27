const double pi=acos(-1.0);
struct Transform
{
    typedef complex<double> cp;
    vi r;
    int n2;
    void FFT(vector<cp> &a,int opt) // opt=1 -> DFT, opt=-1 -> iDFT
    {
        rep(i,1,n2-1) if(r[i]>i) swap(a[i],a[r[i]]);
        vector<cp> w;
        for(int step=1;step<n2;step<<=1)
        {
            w.resize(step);
            rep(j,0,step-1) 
            {
                db theta=pi*j/step*opt;
                w[j]=cp{cos(theta),sin(theta)};
            }
            for(int step2=step<<1,i=0;i<n2;i+=step2)
            {
                rep(j,0,step-1)
                {
                    cp even=a[i+j];
                    cp odd=a[i+j+step];
                    cp tmp=w[j]*odd;
                    a[i+j]=even+tmp;
                    a[i+j+step]=even-tmp;
                }
            }
        }
    }
    void pre(int n) // set n2, r;
    {
        int len=0;
        for(n2=1;n2<n;n2<<=1) len++;
        r.resize(n2);
        rep(i,1,n2-1) r[i]=(r[i>>1]>>1)|((i&1)<<(len-1));
    }
    vi conv(vi &a,vi &b)
    {
        int n=a.size()+b.size()-1;
        pre(n);
        vector<cp> x(n2,0),y(n2,0);
        rep(i,0,sz(a)-1) x[i]=a[i];
        rep(i,0,sz(b)-1) y[i]=b[i];
        
        FFT(x,1); FFT(y,1);
        rep(i,0,n2-1) x[i]*=y[i];
        FFT(x,-1);
        vi c(n2,0);
        rep(i,0,n2-1) c[i]=x[i].real()/n2+0.5;
        c.resize(n);
        return c;
    }
    void work(vector<cp> &a,vector<cp> &b,vi &ans,int w,int mod)
    {
        vector<cp> tmp(n2,0);
        rep(i,0,n2-1) tmp[i]=a[i]*b[i];
        FFT(tmp,-1);
        rep(i,0,n2-1) ans[i]=(ans[i]+(ll)(tmp[i].real()/n2+0.5)%mod*w)%mod;
    }
    vi conv(vi &a,vi &b,int mod)
    {
        int M=sqrt(mod)+0.5;
        int n=a.size()+b.size()-1;
        pre(n);
        vector<cp> A(n2,0),B(n2,0),C(n2,0),D(n2,0);
        rep(i,0,sz(a)-1) A[i]=a[i]/M,B[i]=a[i]%M;
        rep(i,0,sz(b)-1) C[i]=b[i]/M,D[i]=b[i]%M;

        FFT(A,1); FFT(B,1); FFT(C,1); FFT(D,1);
        vi c(n2,0);
        work(A,C,c,1ll*M*M%mod,mod);
        work(B,D,c,1,mod);
        work(A,D,c,M,mod);
        work(B,C,c,M,mod);
        c.resize(n);
        return c;
    }
}fft;