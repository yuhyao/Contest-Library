struct Euler_order
{
    #define LG 18
    array<int,maxn+5> in;
    array<int,maxn*2+5> a,lg;
    int tot;
    pii st[LG][maxn*2+5];
    void dfs(int now,int fa)
    {
        a[++tot]=now; in[now]=tot; 
        for(auto v: e[now]) if(v!=fa) {dfs(v,now); a[++tot]=now;}
    }
    void init(int n)
    {
        int N=n*2-1;
        rep(i,2,N) lg[i]=lg[i>>1]+1;
        tot=0;
        dfs(1,0);
        rep(i,1,N) st[0][i]={in[a[i]],a[i]};
        rep(i,1,lg[N]) rep(j,1,N-(1<<i)+1) st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    }
    int lca(int u,int v) // ask the lca of vertices u and v. 
    {
        int l=in[u],r=in[v];
        if(l>r) swap(l,r);
        int k=lg[r-l+1];
        return min(st[k][l],st[k][r-(1<<k)+1]).SE;
    }
    #undef LG
}eu;