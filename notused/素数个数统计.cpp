//时间复杂度为O(sqrt(n))。
#include<bits/stdc++.h>
#define sqrt_maxn 400000
using namespace std;
int b[sqrt_maxn+5];
int s[sqrt_maxn+5];
long long n;
void getprime(int n)
{
    int i,j;
    for(i=2;i<=n;i++) if(!b[i])
    {
        if(n/i<i) break;
        for(j=i*i;j<=n;j+=i) b[j]=1;
    }
    for(i=2;i<=n;i++)
    {
        s[i]=s[i-1];
        if(!b[i]) s[i]++;
    }
    return;
}
long long dfs(long long n,long long p)
{
    if(p*p>n)
    {
        if (n<sqrt_maxn)
        return s[n];
        else p=sqrt(n);
    }
    if(p<=1) return n-1;
    while(b[p]) p--;
    return (dfs(n,p-1)-dfs(n/p,p-1))+s[p-1];
}
int main()
{
    getprime(sqrt_maxn);
    while(scanf("%lld",&n)==1)
    {
        printf("%lld\n",dfs(n,(long long)sqrtl(n)));
    }
    return 0;
}
