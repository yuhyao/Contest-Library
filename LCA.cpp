const int LG=20;
int dep[maxn+5],anc[LG][maxn+5];
vi e[maxn+5];

void dfs(int now,int fa)
{
    anc[0][now]=fa; dep[now]=dep[fa]+1;
    for(auto v: e[now]) if(v!=fa) dfs(v,now);
}
int swim(int x,int h)
{
    rep(i,0,LG-1) if(h>>i&1) x=anc[i][x];
    return x;
}
int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    x=swim(x,dep[x]-dep[y]);
    if(x==y) return x;
    per(i,0,LG-1) if(anc[i][x]!=anc[i][y]) x=anc[i][x],y=anc[i][y];
    return anc[0][x];
}
int main()
{
    dfs(1,0);
    rep(i,1,LG-1) rep(j,1,n) anc[i][j]=anc[i-1][anc[i-1][j]];
}
