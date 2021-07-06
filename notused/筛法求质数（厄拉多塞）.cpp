#include<bits/stdc++.h>
#define rep(i,a,n) for(i=a;i<=n;i++)
#define maxn 1000000
using namespace std;
bool isnotprime[maxn+5]={1,1};
int main()
{
    int i,j,gen=(int)sqrt(maxn)+1;
    rep(i,2,gen)
    {
        if(!isnotprime[i]) for(j=i*i;j<=maxn;j+=i) isnotprime[j]=1;
    }
    return 0;
}
