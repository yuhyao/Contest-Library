ll qp(ll a,ll k)
{
    ll res=1;
    for(;k;a=a*a%mod,k>>=1) if(k&1) res=res*a%mod;
    return res;
}

struct Mat // indices start from 1.
{
    int n,m;
    int a[maxn+5][maxn*2+5];
    int* operator [](const int &i) const {return (int*)a[i];}
    Mat(int x=0,int y=0): n(x),m(y) {memset(a,0,sizeof a);}
    Mat operator + (const Mat &b) const
    {
        Mat c(n,m);
        rep(i,1,n) rep(j,1,m) c[i][j]=(a[i][j]+b[i][j])%mod;
        return c;
    }
    Mat operator - (const Mat &b) const
    {
        Mat c(n,m);
        rep(i,1,n) rep(j,1,m) c[i][j]=(a[i][j]-b[i][j]+mod)%mod;
        return c;
    }
    Mat operator *(const Mat &b) const
    {
        Mat c(n,b.m);
        rep(i,1,n) rep(j,1,b.m) rep(k,1,m) c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
        return c;
    }
};

int Gaussian(Mat &A,int C) // do elimination up to C columns
{
    int rk=0, n=A.n, m=A.m;
    rep(c,1,C)
    {
        int id=rk+1;
        while(id<=n && A[id][c]==0) id++;
        if(id>n) continue; 
        rk++;
        if(id!=rk) rep(j,1,m) swap(A[id][j],A[rk][j]);
        int inv = qp(A[rk][c],mod-2);
        rep(j,1,m) A[rk][j] = 1ll*A[rk][j]*inv%mod;
        rep(i,1,n) if(i!=rk)
        {
            int fac = (mod-A[i][c])%mod;
            rep(j,1,m) A[i][j] = (A[i][j] + 1ll*fac*A[rk][j])%mod;
        }
    }
    return rk;
}

Matrix inverse(Matrix A)//求矩阵A的逆矩阵
{
    int id,n=A.n;
    Matrix B(n,n*2),C(n,n);
    rep(i,1,n) rep(j,1,n) B.data[i][j]=A.data[i][j];
    rep(i,1,n) B.data[i][i+n]=1;
    rep(i,1,n)
    {
        for(id=i;id<=n;id++) if(B.data[id][i]!=0) break;
        if(id!=i) rep(k,1,2*n) swap(B.data[i][k],B.data[id][k]);
        double tmp=B.data[i][i];
        rep(j,1,2*n) B.data[i][j]/=tmp;
        rep(j,1,n)
        {
            if(j==i) continue;
            tmp=B.data[j][i];
            rep(k,1,2*n) B.data[j][k]-=tmp*B.data[i][k];
        }
    }
    rep(i,1,n) rep(j,1,n) C.data[i][j]=B.data[i][j+n];
    return C;
}
//求矩阵A的秩，如果矩阵元素是实数一定要加上eps
int Mrank(Matrix A)
{
    Matrix B=A;
    int id,cnt=1,n=A.n,m=A.m;
    rep(i,1,m)
    {
        for(id=cnt;id<=n;id++) if(B.data[id][i]!=0) break;
        if(id==n+1) continue;
        if(id!=cnt) rep(k,1,m) swap(B.data[cnt][k],B.data[id][k]);
        if(B.data[cnt][i]<0) rep(k,1,m) B.data[cnt][k]*=-1;
        rep(j,cnt+1,n)
        {
            if(B.data[j][i]<0) rep(k,1,m) B.data[j][k]*=-1;
            int GCD=gcd(B.data[cnt][i],B.data[j][i]);
            int tmp=B.data[j][i]/GCD;
            rep(k,1,m) B.data[j][k]=B.data[j][k]*(B.data[cnt][i]/GCD)-tmp*B.data[cnt][k];
        }
        cnt++;
    }
    return cnt-1;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    Matrix A(n,m);
    rep(i,1,n) rep(j,1,m) scanf("%lf",&A.data[i][j]);
    printf("%d\n",Mrank(A));
    return 0;
}
