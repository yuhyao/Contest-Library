// Time Complexity: O(n sqrt{m})
struct qnode {int l,r,id;} q[maxn+5];
void solve(int n,int m) 
{
    int sz=ceil(n/sqrt(m));
    rep(i,1,m) scanf("%d%d",&q[i].l,&q[i].r),q[i].id=i;
    sort(q+1,q+m+1,[&](qnode &a,qnode &b) {
        return a.l/sz==b.l/sz?a.r<b.r:a.l<b.l;
    });
    int l=1,r=0;
    rep(i,1,m)
    {
        // ...
    }
}
