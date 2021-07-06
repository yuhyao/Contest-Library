#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 10
#define maxm 10
using namespace std;

int gcd(int a,int b){return (b==0)?a:gcd(b,a%b);}
struct Matrix
{
    int n,m;//n是行数，m是列数
    int data[maxn+5][maxm*2+5];//处理实矩阵时用double，同时注意%不能使用
    //maxm*2是为了防止矩阵求逆时越界
    void Clear(){memset(data,0,sizeof data);}
    Matrix(int x=0,int y=0):n(x),m(y){Clear();}//防止不必要的错误
    Matrix operator +(const Matrix &A) const
    {
        Matrix C(n,m);
        rep(i,1,n) rep(j,1,m) C.data[i][j]=data[i][j]+A.data[i][j];
        return C;
    }
    Matrix operator -(const Matrix &A) const
    {
        Matrix C(n,m);
        rep(i,1,n) rep(j,1,m) C.data[i][j]=data[i][j]-A.data[i][j];
        return C;
    }
    Matrix operator *(const Matrix &A) const
    {
        Matrix C(n,A.m);
        rep(i,1,n) rep(j,1,A.m) rep(k,1,m)
            C.data[i][j]+=data[i][k]*A.data[k][j];
        return C;
    }
    Matrix operator %(const int &mod) const
    {
        Matrix C(n,m);
        rep(i,1,n) rep(j,1,m) C.data[i][j]=data[i][j]%mod;
        return C;
    }
    bool operator ==(const Matrix &A) const
    {
        if(m!=A.m || n!=A.n) return 0;
        rep(i,1,n) rep(j,1,m) if(data[i][j]!=A.data[i][j]) return 0;
        return 1;
    }
};
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
int Mrank(Matrix A)//求矩阵A的秩，如果矩阵元素是实数一定要加上eps
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
