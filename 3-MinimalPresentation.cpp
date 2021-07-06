#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 100000
using namespace std;
char s[maxn+5];
int minP(char* s)//返回最小（最大）表示的最小首个字符下标，从0开始。
{
    int n=strlen(s);
    int i=0,j=1,k=0,t;
    while(i<n && j<n && k<n)
    {
        t=s[(i+k)%n]-s[(j+k)%n];
        if(!t) k++;
        else
        {
            if(t>0) i+=k+1;
            else j+=k+1;
            if(i==j) j++;
            k=0;
        }
    }
    return i<j?i:j;
}
int main()
{
    while(~scanf("%s",s)) printf("%d\n",minP(s));
    return 0;
}
