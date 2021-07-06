#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 100000
using namespace std;
int fail[maxn+5];
void calfail(char *p)
{
    int j=0,l=strlen(p);
    fail[0]=0;
    rep(i,1,l-1)
    {
        while(j && p[j]!=p[i]) j=fail[j-1];
        if(p[j]==p[i]) j++;
        fail[i]=j;
    }
    return;
}
vi kmp(char *p,char *t)
{
    int n=strlen(t),m=strlen(p),j=0;
    vi match(n,0);
    rep(i,0,n-1)
    {
        while(j && (j==m || p[j]!=t[i])) j=fail[j-1];
        if(p[j]==t[i]) j++;
        match[i]=(j==m);
    }
    return match;
}
int main()
{
    return 0;
}
