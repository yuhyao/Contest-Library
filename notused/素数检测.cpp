#include<iostream>
#include<iostream>
#include<cstdio>
using namespace std;
int prime[15]={0,2,3,5,7,11};
long long fast_pow(int a,int d,int mod)//二分幂（注意函数类型，选择long long比较稳妥）
{
    if(d==0) return 1;
    long long tmp=fast_pow(a,d/2,mod);
    tmp=tmp*tmp%mod;
    if(d&1) tmp=tmp*(long long)a%mod;
    return tmp;
}
bool test(int x,int a)
{
    if(x==a) return 1;
    if(x%2==0) return 0;
    int d=x-1;
    long long tmp;
    while(!(d&1)) d>>=1;
    tmp=fast_pow(a,d,x);
    if(tmp==1) return 1;
    while(d<x-1)
    {
        d<<=1;
        if(tmp==x-1) return 1;
        tmp=tmp*tmp%x;
    }
    return 0;
}
bool miller(int x)//判断x是否是素数，是则返回1，不是则返回0。
{
    if(x<2) return 0;
    if(x==2) return 1;
    int i;
    for(i=1;i<=4;i++)
    {
        if(!test(x,prime[i])) return 0;//选取底数进行测试，int以内2、3、5、7作为底数足够了
    }
    return 1;
}
int main()
{
    return 0;
}
