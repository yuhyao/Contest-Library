#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 100000
using namespace std;
//fread 读入挂
inline char nc()
{
    static char buf[100000],*p1=buf,*p2=buf;
    return p1==p2 && (p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline int read()
{
    int x=0,sgn=1;
    char ch=nc();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') sgn=-1;
        ch=nc();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=nc();
    }
    return x*sgn;
}
//普通读入优化
int read()
{
    int x=0,sgn=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') sgn=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*sgn;
}
int main()
{
    return 0;
}