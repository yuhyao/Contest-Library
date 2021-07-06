struct Blossom
{
    int n,tot;
    vector<vi> e;
    vi match,cmp,fa,pre,clr;
    queue<int> Q;
    void init(int _n)
    {
        n=_n; tot=0;
        e=vector<vi>(n+1,vi{});
        match=cmp=fa=pre=clr=vi(n+5,0);
    }
    // add a bidirectional edge
    void addedge(int u,int v) {e[u].pb(v); e[v].pb(u);}
    int getfa(int x) {return fa[x]==x?x:fa[x]=getfa(fa[x]);}
    int lca(int x,int y)
    {
        tot++;
        x=getfa(x); y=getfa(y);
        while(cmp[x]!=tot)
        {
            cmp[x]=tot;
            x=getfa(pre[match[x]]);
            if(y) swap(x,y);
        }
        return x;
    }
    void shrink(int x,int y,int par)
    {
        while(getfa(x)!=par)
        {
            pre[x]=y; y=match[x];
            if(clr[y]==2) clr[y]=1,Q.push(y);
            if(getfa(x)==x) fa[x]=par;
            if(getfa(y)==y) fa[y]=par;
            x=pre[y];
        }
    }
    bool aug(int st)
    {
        rep(i,1,n) fa[i]=i;
        rep(i,1,n) clr[i]=pre[i]=0;
        Q=queue<int>{};
        Q.push(st); clr[st]=1; // 1 is black.
        while(Q.size())
        {
            int now=Q.front(); Q.pop();
            for(auto v: e[now])
            {
                if(getfa(now)==getfa(v) || clr[v]==2) continue;
                if(clr[v]==0)
                {
                    clr[v]=2;
                    pre[v]=now;
                    if(match[v]==0)
                    {
                        for(int x=v,y;x;x=y)
                        {
                            y=match[pre[x]];
                            match[x]=pre[x];
                            match[pre[x]]=x;
                        }
                        return 1;
                    }
                    clr[match[v]]=1;
                    Q.push(match[v]);
                }
                else if(clr[v]==1)
                {
                    int _lca=lca(now,v);
                    shrink(now,v,_lca);
                    shrink(v,now,_lca);
                }
            }
        }
        return 0;
    }
	int work()
    {
        int ans=0;
        rep(i,1,n) if(match[i]==0) ans+=aug(i);
        return ans;
    }
};