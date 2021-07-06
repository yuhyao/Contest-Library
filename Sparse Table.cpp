template<class T> struct SparseTable
{
    #define LG 20
    int lg[maxn+5];
    T st[LG][maxn+5];
    T ask(int l,int r)
    {
        int k=lg[r-l+1];
        return min(st[k][l],st[k][r-(1<<k)+1]);
    }
    void init(int n,T a[]) // index starts from 1.
    {
        rep(i,2,n) lg[i]=lg[i>>1]+1;
        rep(i,1,n) st[0][i]=a[i];
        rep(i,1,lg[n]) rep(j,1,n-(1<<i)+1) st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    }
    #undef LG
};

int st2[MAXN+5][MAXN+5][12][12],lg[maxn+5];
int query2(int l1,int r1,int l2,int r2)
{
    int k1=lg[l2-l1+1],k2=lg[r2-r1+1];
    int a,b,c,d;
    a=st2[l1][r1][k1][k2];
    b=st2[l2-(1<<k1)+1][r1][k1][k2];
    c=st2[l1][r2-(1<<k2)+1][k1][k2];
    d=st2[l2-(1<<k1)+1][r2-(1<<k2)+1][k1][k2];
    return min(a,min(b,min(c,d)));
}
void init2(int n,int m)
{
    rep(i,1,lg[n]) rep(k,1,n-(1<<i)+1) rep(l,1,m) st2[k][l][i][0]=min(st2[k][l][i-1][0],st2[k+(1<<i-1)][l][i-1][0]);
    rep(j,1,lg[m]) rep(i,0,lg[n]) rep(k,1,n-(1<<i)+1) rep(l,1,m-(1<<j)+1) st2[k][l][i][j]=min(st2[k][l][i][j-1],st2[k][l+(1<<j-1)][i][j-1]);
    return;
}
