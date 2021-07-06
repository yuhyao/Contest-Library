#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 10000
using namespace std;
int n,x[maxn+5],y[maxn+5],w[maxn+5];
double ansx,ansy,dis;

double Rand() 
{
    return (double)rand()/RAND_MAX;
}
double calc(double xx,double yy) 
{
    double res=0;
    rep(i,1,n)
    {
        double dx=x[i]-xx,dy=y[i]-yy;
        res+=sqrt(dx*dx+dy*dy)*w[i];
    }
    if(res<dis) dis=res,ansx=xx,ansy=yy;
    return res;
}
void simulateAnneal() 
{
    double t=100000;
    double nowx=ansx,nowy=ansy;
    while(t>0.001) 
    {
        double nxtx=nowx+t*(Rand()*2-1);
        double nxty=nowy+t*(Rand()*2-1);
        double delta=calc(nxtx,nxty)-calc(nowx,nowy);
        if(exp(-delta/t)>Rand()) nowx=nxtx,nowy=nxty;
        t*=0.97;
    }
    rep(i,1,1000)
    {
        double nxtx=ansx+t*(Rand()*2-1);
        double nxty=ansy+t*(Rand()*2-1);
        calc(nxtx,nxty);
    }
}
int main() {
    srand(time(0));
    scanf("%d",&n);
    rep(i,1,n)
    {
        scanf("%d%d%d",&x[i],&y[i],&w[i]);
        ansx+=x[i];ansy+=y[i];
    }
    ansx/=n,ansy/=n,dis=calc(ansx,ansy);
    simulateAnneal();
    printf("%.3lf %.3lf\n",ansx,ansy);
    return 0;
}