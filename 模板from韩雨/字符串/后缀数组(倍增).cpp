#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

const int maxn=300000;

int wa[maxn],wb[maxn],wv[maxn],ws[maxn];
bool cmp(int *r,int a,int b,int l)
    {return r[a]==r[b] && r[a+l]==r[b+l];}
void da(int *r,int *sa,int n,int m)
{
    int *x=wa,*y=wb,*t;
    for (int i=0;i<m;++i) ws[i]=0;
    for (int i=0;i<n;++i) ws[x[i]=r[i]]++;
    for (int i=1;i<m;++i) ws[i]+=ws[i-1];
    for (int i=n-1;i>=0;i--) sa[--ws[x[i]]]=i;
    for (int i=0,j=1,p=0;p<n;j*=2,m=p)
    {
        for (p=0,i=n-j;i<n;i++) y[p++]=i;
        for (i=0;i<n;++i) if (sa[i]>=j) y[p++]=sa[i]-j;
        for (i=0;i<m;++i) ws[i]=0;
        for (i=0;i<n;++i) ws[x[y[i]]]++;
        for (i=1;i<m;++i) ws[i]+=ws[i-1];
        for (i=n-1;i>=0;--i) sa[--ws[x[y[i]]]]=y[i];
        for (t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;++i)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}

int height[maxn],rankk[maxn];
void calheight(int *r,int *sa,int n)
{
    for (int i=1;i<=n;++i) rankk[sa[i]]=i;
    for (int i=0,j=0,k=0;i<n;height[rankk[i++]]=k)
        for (k?--k:0,j=sa[rankk[i]-1];r[i+k]==r[j+k];k++);
    return;
}
