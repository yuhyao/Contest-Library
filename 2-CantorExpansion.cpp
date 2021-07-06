#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 10
using namespace std;
int fac[maxn+5],data[maxn+5];
bool used[maxn+5];
void cal_fac(int n)
{
    fac[0]=1;
    rep(i,1,n) fac[i]=fac[i-1]*i;
    return;
}
int ArrayToInt(int a[],int n)//将全排列序列data[]转换其在所有n阶全排列中的排名，排名从0到n!-1。
{
    int ans=0;
    rep(i,1,n-1)
    {
        int tmp=0;
        rep(j,i+1,n) tmp+=(a[i]>a[j]);
        ans+=tmp*fac[n-i];
    }
    return ans;
}
void IntToArray(int a[],int n,int x)//将x对应的n阶全排列存储至data[]中。
{
    memset(used,0,sizeof used);
    rep(i,1,n)
    {
        int tmp=x/fac[n-i];
        rep(j,1,n)
        {
            if(!used[j])
            {
                if(tmp==0)
                {
                    used[j]=1;
                    a[i]=j;
                    break;
                }
                tmp--;
            }
        }
        x%=fac[n-i];
    }
    return;
}
int main()
{
    int n,x;
    scanf("%d%d",&n,&x);
    cal_fac(n);
    IntToArray(data,n,x);
    rep(i,1,n) printf("%d: %d\n",i,data[i]);
    printf("%d\n",ArrayToInt(data,n));
    return 0;
}
