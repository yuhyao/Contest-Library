#include<bits/stdc++.h>
#define maxn 100000
using namespace std;
int data[maxn+5]={0,2,3,4,5,6,7,7,8,8,8,8,9,10,12,17};
int lb(int l,int r,int x)
{
    r++;
    int mid;
    while(l<r)
    {
        mid=(l+r)/2;
        if(data[mid]>=x) r=mid;//(1)
        else l=mid+1;
    }
    return r;
}
/*
    单调不减数列找第一个大于等于x的下标。若找最后一个小于x的下标则取返回值减1。
    单调不减数列找第一个大于x的下标就将(1)中的>=换成>。若找最后一个小于等于x的下标则取返回值减1。
    单调不增数列找第一个小于等于x的下标就将(1)中的>=换成<=。若找最后一个大于x的下标则取返回值减1。
    单调不增数列找第一个小于x的下标就将(1)中的>=换成<。若找最后一个大于等于x的下标则取返回值减1。
*/
int main()
{
    int n;
    printf("%d\n",lb(1,15,18));
    return 0;
}
