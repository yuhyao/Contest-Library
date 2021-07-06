#include<cmath>
#include<complex>
#include<cstring>
using namespace std;

typedef long long LL;
const int maxn=1500000;
const double pi=acos(-1.0);

typedef complex<double> Complex;

void build(Complex _P[], Complex P[],int n,int m,int curr,int &cnt){
    if (m==n){
        _P[curr]=P[cnt++];
    }    else {
        build(_P, P, n,m*2,curr,cnt);
        build(_P, P, n,m*2,curr+m,cnt);
    }
}

Complex ans[1500000],temp[1500000];

void FFT(Complex P[], int n,int oper){
    static Complex _P[maxn];
    int cnt=0;
    build(_P,P,n,1,0,cnt);
    copy(_P,_P+n,P);
    for (int d=0;(1<<d)<n;d++){
        int m=1<<d;
        int m2=m*2;
        double p0=pi/m*oper;
        Complex unit_p0 = Complex(cos(p0),sin(p0));
        for (int i=0;i<n;i+=m2){
            Complex unit=1;
            for (int j=0;j<m;++j){
                Complex &P1 = P[i+j+m], &P2 = P[i+j];
                Complex t=unit*P1;
                P1=P2-t;
                P2=P2+t;
                unit=unit*unit_p0;        
            }
        }
    }
    if (oper==-1) for (int i=0;i<n;++i)
        P[i]/=n;
}

int multi(int l1,int r1,double *a,double *la,int l2,int r2,double *b,double *lb)
{
    int len1=r1-l1+1,len2=r2-l2+1,len=1,s1,s2;
    if (la>a) s1=1;else s1=-1;
    if (lb>b) s2=1;else s2=-1;
    while (len<len1+len2-1) len<<=1;
    for (int i=l1;i<=r1;++i) ans[i-l1]=Complex((*a),0),a+=s1;
    for (int i=len1;i<len;++i) ans[i]=Complex(0,0);
    for (int i=l2;i<=r2;++i) temp[i-l2]=Complex((*b),0),b+=s2;
    for (int i=len2;i<len;++i) temp[i]=Complex(0,0);
    FFT(ans,len,1);FFT(temp,len,1);
    for (int i=0;i<len;++i) ans[i]=ans[i]*temp[i];
    FFT(ans,len,-1);
    return -l1-l2;
}

