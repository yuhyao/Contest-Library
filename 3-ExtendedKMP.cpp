#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 1000000
#define mod 1000000007
using namespace std;
char s1[maxn+5],s2[maxn*2+5];
int lcp[maxn+5],extend[maxn*2+5];
void get_lcp(char* p)
{
    int m=strlen(p),p0=0,r=-1;
    lcp[0]=m;
    rep(k,0,m-2)
    {
        if(r>k && r-k>lcp[k+1-p0]) lcp[k+1]=lcp[k+1-p0];
        else
        {
            int i;
            for(i=max(k,r);p[i+1]==p[i-k];i++);
            lcp[k+1]=i-k;
            if(i>r) r=i,p0=k+1;
        }
    }
    return;
}
void get_ext(char* t,char* p)
{
    int n=strlen(t),m=strlen(p),p0=0,r=-1;
    rep(k,-1,n-2)
    {
        if(r>k && r-k>lcp[k+1-p0]) extend[k+1]=lcp[k+1-p0];
        else
        {
            int i;
            for(i=max(k,r);t[i+1]==p[i-k] && p[i-k];i++);
            extend[k+1]=i-k;
            if(i>r) r=i,p0=k+1;
        }
    }
    return;
}
int main()
{
    while(~scanf("%s",s1))
    {
        get_lcp(s1);
        int n=strlen(s1);
        rep(i,0,n-1) printf("%d: %d\n",i,lcp[i]);
    }
    return 0;
}
