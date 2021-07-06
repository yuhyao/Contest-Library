struct HLD
{
    array<int,maxn+5> fa,sz,heavy,id,dep,top;
    int n,cnt;
    
    void dfs(int now)
    {
        sz[now]=1;
        heavy[now]=-1;
        int mx=0;
        for(auto v: e[now]) if(dep[v]==0) 
        {
            dep[v]=dep[now]+1;
            fa[v]=now;
            dfs(v);
            sz[now]+=sz[v];
            if(chmax(mx,sz[v])) heavy[now]=v;
        }
    }
    void getid(int now,int sp)
    {
        top[now]=sp;
        id[now]=++cnt;
        if(heavy[now]==-1) return;
        getid(heavy[now],sp);
        for(auto v: e[now]) 
        {
            if(v==heavy[now] || v==fa[now]) continue;
            getid(v,v);
        }
    }
    void init(int _n)
    {
        n=_n;
        rep(i,1,n) dep[i]=0;
        dep[1]=1; cnt=0;
        dfs(1);
        getid(1,1);
        seg.build(1,1,n);
    }
    int lca(int u,int v)
    {
        while(top[u]!=top[v])
        {
            if(dep[top[u]]<dep[top[v]]) swap(u,v);
            u=fa[top[u]];
        }
        if(dep[u]<dep[v]) return u;
        return v;
    }
    // the following codes are for the edges on a chain.
    void add(int u,int v)
    {
        int f1=top[u],f2=top[v];
        while(f1!=f2)
        {
            if(dep[f1]<dep[f2]) swap(f1,f2),swap(u,v);
            seg.add(1,1,n,id[f1],id[u]);
            u=fa[f1];f1=top[u];
        }
        if(u==v) return;
        if(dep[u]<dep[v]) swap(u,v);
        seg.add(1,1,n,id[heavy[v]],id[u]);
        return;
    }
    int ask(int u,int v)
    {
        int f1=top[u],f2=top[v];
        int ans=0;
        while(f1!=f2)
        {
            if(dep[f1]<dep[f2]) swap(f1,f2),swap(u,v);
            ans+=seg.ask(1,1,n,id[f1],id[u]);
            u=fa[f1];f1=top[u];
        }
        if(u!=v)
        {
            if(dep[u]<dep[v]) swap(u,v);
            ans+=seg.ask(1,1,n,id[heavy[v]],id[u]);
        }
        return ans;
    }
}hld;