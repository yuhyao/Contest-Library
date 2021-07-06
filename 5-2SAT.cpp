struct _2sat_solver
{
    vector<vi> e;
    vi dfn,low,sta,scc,value;
    int cnt,tot,top,n;
    _2sat_solver(){n=-1;}
    // always initialize before using the solver.
    void init(int _n)
    {
        n=_n;
        e=vector<vi>(n*2+5,vi{});
        dfn=low=scc=sta=vi(n*2+5,0);
        value=vi(n+5,0);
        cnt=tot=top=0;
    }
    // e.g. if you want to add constrant (not x) or (y), just call add_constraint(x,1,y,0);
    void add_constraint(int x,int neg_x,int y,int neg_y)
    {
        // x_i      i*2
        // not x_i  i*2+1
        x=x*2+neg_x;
        y=y*2+neg_y;
        e[x^1].pb(y);
        e[y^1].pb(x);
    }
    void set_pos(int x) {add_constraint(x,0,x,0);}
    void set_neg(int x) {add_constraint(x,1,x,1);}

    void tarjan(int now)
    {
        dfn[now]=low[now]=++cnt;
        sta[++top]=now;
        for(auto v: e[now])
        {
            if(dfn[v]==0)
            {
                tarjan(v);
                low[now]=min(low[now],low[v]);
            }
            else if(scc[v]==0) low[now]=min(low[now],dfn[v]);
        }
        if(low[now]==dfn[now])
        {
            tot++;
            while(sta[top]!=now) scc[sta[top--]]=tot;
            scc[sta[top--]]=tot;
        }
    }
    bool solve()
    {
        // check if initialized.
        assert(n!=-1);
        // start solving the system:
        rep(i,2,n*2+1) if(dfn[i]==0) tarjan(i);
        rep(i,1,n)
        {
            if(scc[i*2]==scc[i*2+1]) return 0;
            value[i]=(scc[i*2]<scc[i*2+1]); // scc[x_i] < scc[not x_i] means x_i should be true.
        }
        return 1;
    }
};