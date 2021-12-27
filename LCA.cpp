const int LG=__lg(maxn)+1;
int dep[maxn+5],anc[maxn+5][LG];
vi e[maxn+5];

void dfs(int now,int fa)
{
    dep[now]=dep[fa]+1; anc[now][0]=fa; rep(i,1,LG-1) anc[now][i]=anc[anc[now][i-1]][i-1];
    for(auto v: e[now]) if(v!=fa) dfs(v,now);
}
int swim(int x,int h)
{
    rep(i,0,LG-1) if(h>>i&1) x=anc[x][i];
    return x;
}
int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    x=swim(x,dep[x]-dep[y]);
    if(x==y) return x;
    per(i,0,LG-1) if(anc[x][i]!=anc[y][i]) x=anc[x][i],y=anc[y][i];
    return anc[x][0];
}