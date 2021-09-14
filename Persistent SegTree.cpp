#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 100000
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<ll,int> pii;
int a[maxn+5];

struct persistent_segtree
{
    #define lsx ls[x]
    #define rsx rs[x]
    #define lsy ls[y]
    #define rsy rs[y]
    #define MAXN (maxn*(4+21))

    int tot;
    array<int,MAXN+5> ls,rs,cnt;

    void init() {tot=0;}
    void upd(int x,int &y,int l,int r,int v) // a[v]++, where v \in [1,n].
    {
        y=++tot; tie(lsy,rsy,cnt[y])={lsx,rsx,cnt[x]}; cnt[y]++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(v<=mid) upd(lsx,lsy,l,mid,v);
        else upd(rsx,rsy,mid+1,r,v);
    }
	// find the largest v such that sum_{i<v} a[i] is less than k. 
	// i.e. the k-th smallest value.
    int ask(int x,int y,int l,int r,int k) 
    {
        if(l==r) return l;
        int mid=(l+r)>>1;
        int C=cnt[lsy]-cnt[lsx];
        if(k<=C) return ask(lsx,lsy,l,mid,k);
        else return ask(rsx,rsy,mid+1,r,k-C);
    }
	// calculate sum_{i<=v} a[i].
    int query_less(int x,int y,int l,int r,int v) 
    {
        if(v>r) return cnt[y]-cnt[x];
        if(v<=l) return 0;
        int mid=(l+r)>>1;
        return query_less(lsx,lsy,l,mid,v)+query_less(rsx,rsy,mid+1,r,v);
    }
    int query_greater(int x,int y,int l,int r,int v)
    {
        if(v<l) return cnt[y]-cnt[x];
        if(v>=r) return 0;
        int mid=(l+r)>>1;
        return query_greater(lsx,lsy,l,mid,v)+query_greater(rsx,rsy,mid+1,r,v);
    }

    #undef lsx
    #undef rsx
    #undef lsy
    #undef rsy
    #undef MAXN
}pseg;

int root[maxn+5];

int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    init();
    rep(i,1,n) scanf("%d",&a[i]);
    rep(i,1,n) upd(1,n,root[i-1],root[i],a[i]);
    while(m--)
    {
        int L,R,k;
        scanf("%d%d%d",&L,&R,&k);
        printf("%d\n",query(1,n,root[L-1],root[R],k));
    }
    return 0;
}
