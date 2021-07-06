#include<iostream>
#include<iostream>
#include<cstdio>
using namespace std;
int prime[15]={0,2,3,5,7,11};
long long fast_pow(int a,int d,int mod)//�����ݣ�ע�⺯�����ͣ�ѡ��long long�Ƚ����ף�
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
bool miller(int x)//�ж�x�Ƿ������������򷵻�1�������򷵻�0��
{
    if(x<2) return 0;
    if(x==2) return 1;
    int i;
    for(i=1;i<=4;i++)
    {
        if(!test(x,prime[i])) return 0;//ѡȡ�������в��ԣ�int����2��3��5��7��Ϊ�����㹻��
    }
    return 1;
}
int main()
{
    return 0;
}
