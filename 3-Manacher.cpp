#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 100000
using namespace std;
char Ma[maxn*2+5],s[maxn+5];
int Mp[maxn*2+5];
int manacher(char* s)//返回s中最长回文子串的长度。
{
    int l=0,n=strlen(s);
    Ma[l++]='$';
    Ma[l++]='#';
    rep(i,0,n-1)
    {
        Ma[l++]=s[i];
        Ma[l++]='#';
    }
    Ma[l]=0;
    int mx=0,id=0;
    rep(i,0,l-1)
    {
        Mp[i]=mx>i?min(Mp[2*id-i],mx-i):1;
        while(Ma[i+Mp[i]]==Ma[i-Mp[i]]) Mp[i]++;
        if(i+Mp[i]>mx)
        {
            mx=i+Mp[i];
            id=i;
        }
    }
    int ans=0;
    rep(i,0,2*n+1) ans=max(ans,Mp[i]-1);
    return ans;
}
int main()
{
    while(~scanf("%s",s)) printf("%d\n",manacher(s));
    return 0;
}
