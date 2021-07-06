#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 500000
using namespace std;
typedef long long ll;
int a[maxn+5];
struct qnode {int l,r,id;} q[maxn+5];

ll answay[maxn+5],anstot[maxn+5];
ll num[maxn+5];

int main()
{
    int n,m; scanf("%d%d",&n,&m);
    int sz=ceil(n/sqrt(m));
    rep(i,1,n) scanf("%d",&a[i]);
    rep(i,1,m) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
    sort(q+1,q+m+1,[&](qnode a,qnode b) {
        return a.l/sz==b.l/sz?a.r<b.r:a.l<b.l;
    });
    memset(num,0,sizeof num);
    int l=1,r=1;
    ll sum=0;
    num[a[1]]=1;
    rep(i,1,m)
    {
        while(r<q[i].r)
        {
            sum+=num[a[++r]];
            num[a[r]]++;
        }
        while(r>q[i].r)
        {
            num[a[r]]--;
            sum-=num[a[r--]];
        }
        while(l>q[i].l)
        {
            sum+=num[a[--l]];
            num[a[l]]++;
        }
        while(l<q[i].l)
        {
            num[a[l]]--;
            sum-=num[a[l++]];
        }
        answay[q[i].id]=sum;
        anstot[q[i].id]=1ll*(r-l+1)*(r-l)/2;
    }
    rep(i,1,m)
    {
        ll g=__gcd(answay[i],anstot[i]);
        printf("%lld/%lld\n",answay[i]/g,anstot[i]/g);
    }
    return 0;
}
