// indices start from 1.
struct Virtual_Tree
{
    #define LG 20
    vi e[maxn+5], ve[maxn+5]; // ve -> virtual edge.
    array<int,maxn+5> tin,dep,sta;
    int anc[maxn+5][LG],tot;
    void init(int n)
    {
        rep(i,1,n) e[i].clear();
        rep(i,1,n-1)
        {
            int x,y; scanf("%d%d",&x,&y);
            e[x].pb(y); e[y].pb(x);
        }
        tot=0;
        dfs(1,0); // suppose root is 1.
    }
    void dfs(int now,int fa)
    {
        tin[now]=++tot;
        dep[now]=dep[fa]+1;
        anc[now][0]=fa;
        rep(i,1,LG-1) anc[now][i]=anc[anc[now][i-1]][i-1];
        for(auto v: e[now]) if(v!=fa) dfs(v,now);
    }
    int swim(int x,int h)
    {
        debug(x, h);
        for(int i=0;h;i++,h>>=1) if(h&1) x=anc[x][i];
        return x;
    }
    int lca(int x,int y)
    {
        if(dep[x]<dep[y]) swap(x,y);
        x=swim(x,dep[x]-dep[y]);
        if(x==y) return x;
        debug(x, y);
        per(i,0,LG-1)
        {
            if(anc[x][i]==anc[y][i]) continue;
            x=anc[x][i]; y=anc[y][i];
        }
        return anc[x][0];
    }
    void solve(vi A) // build virtual tree for vertex set A.
    {
        sort(all(A),[&](int &x,int &y) {return tin[x]<tin[y];});
        vi vec;
        int top=0;
        for(auto &now: A)
        {
            if(top==0) {sta[++top]=now; continue;}
            int _lca=lca(now,sta[top]);
            debug(now, sta[top], _lca);
            while(top>1 && dep[_lca]<=dep[sta[top-1]]) 
            {
                vec.pb(sta[top]); ve[sta[top-1]].pb(sta[top]); top--;
            }
            if(dep[_lca]<dep[sta[top]]) 
            {
                vec.pb(sta[top]); ve[_lca].pb(sta[top]); top--;
            }
            if(top==0 || _lca!=sta[top]) sta[++top]=_lca;
            sta[++top]=now;
        }
        while(top>1) vec.pb(sta[top]),ve[sta[top-1]].pb(sta[top]),top--;
        vec.pb(sta[top]);
        
        // solve the problem using root = sta[top] here!

        for(auto v: vec) ve[v].clear();
    }
    #undef LG
}vt;