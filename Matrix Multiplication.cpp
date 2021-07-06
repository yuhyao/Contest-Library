const int MatN=2;
typedef array<int,MatN> Vec;
typedef array<Vec,MatN> Mat;

Mat operator *(const Mat &a,const Mat &b)
{
    Mat c{};
    rep(i,0,MatN-1) rep(k,0,MatN-1) rep(j,0,MatN-1) c[i][j]=(c[i][j]+1ll*a[i][k]*b[k][j])%mod;
    return c;
}

Mat qp(Mat a,ll k)
{
    Mat res{}; rep(i,0,MatN-1) res[i][i]=1;
    while(k)
    {
        if(k&1) res=res*a;
        a=a*a;
        k>>=1;
    }
    return res;
}
