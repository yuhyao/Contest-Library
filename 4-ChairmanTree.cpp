#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 100000
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<ll,int> pii;
int a[maxn+5];
struct node
{
    int sum,ls,rs;
}t[maxn*40+5];
int cnt,root[maxn+5];
void upd(int l,int r,int &x,int y,int v)
{
    t[x=++cnt]=t[y];t[x].sum++;
    if(l==r) return;
    int mid=l+r>>1;
    if(v<=mid) upd(l,mid,t[x].ls,t[y].ls,v);
    else upd(mid+1,r,t[x].rs,t[y].rs,v);
}
//问第k大数。
int query(int l,int r,int x,int y,int k)
{
    if(l==r) return l;
    int mid=l+r>>1;
    int sum=t[t[y].ls].sum-t[t[x].ls].sum;
    if(k<=sum) return query(l,mid,t[x].ls,t[y].ls,k);
    else return query(mid+1,r,t[x].rs,t[y].rs,k-sum);
}
//问v的排名（多少个数比v大）
int query_less(int l,int r,int x,int y,int v)
{
    if(v>r) return t[y].sum-t[x].sum;
    if(v<=l) return 0;
    int mid=l+r>>1;
    return query_less(l,mid,t[x].ls,t[y].ls,v)+query_less(mid+1,r,t[x].rs,t[y].rs,v);
}
int query_greater(int l,int r,int x,int y,int v)
{
    if(v<l) return t[y].sum-t[x].sum;
    if(v>=r) return 0;
    int mid=l+r>>1;
    return query_greater(l,mid,t[x].ls,t[y].ls,v)+query_greater(mid+1,r,t[x].rs,t[y].rs,v);
}
void init()
{
    cnt=0;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    init();
    rep(i,1,n) scanf("%d",&a[i]);
    rep(i,1,n) upd(1,n,root[i],root[i-1],a[i]);
    while(m--)
    {
        int L,R,k;
        scanf("%d%d%d",&L,&R,&k);
        printf("%d\n",query(1,n,root[L-1],root[R],k));
    }
    return 0;
}
