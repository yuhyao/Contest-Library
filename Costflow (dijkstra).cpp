namespace costflow
{
    using F = int;
    using C = ll;
    const F MF = 0x3f3f3f3f;
    const C MC = 1ll<<60;
    struct E {int u,v; F c; C w;};
    //Clear when initializing.
    vector<E> e;
    vi to[maxn+5];
    void add(int u,int v,F c,C w)
    {
        to[u].pb(e.size()); e.pb(E{u,v,c,w});
        to[v].pb(e.size()); e.pb(E{v,u,0,-w});
    }
    vector<C> h;
    pair<C,F> work(int n,int src,int sink,F mx_flow = MF)
    {
        h.assign(n+1,0);
        vector<C> dis(n+1);
        vi pre(n+1);

        // ran Bellman-Ford first if necessary.
        rep(i,1,n) dis[i] = MC;
        dis[src] = 0;
        rep(rd,1,n) rep(now,1,n) for(auto i: to[now])
        {
            int v=e[i].v;
            if(e[i].c>0) chmin(dis[v],dis[now]+e[i].w);
        }
        rep(i,1,n) h[i] = dis[i];
    
        priority_queue<pair<C,int> > q;
        C cost=0; F flow = 0;
        while(mx_flow)
        {
            rep(i,1,n) dis[i] = MC;
            rep(i,1,n) pre[i] = -1;
        
            dis[src]=0; q.push({0,src});
        
            while(q.size())
            {
                auto [d,now] = q.top(); q.pop();
                if(d!=-dis[now]) continue;
                for(auto i: to[now])
                {
                    int v=e[i].v;
                    if(e[i].c>0 && chmin(dis[v],dis[now]+e[i].w+h[now]-h[v]))
                    {
                        q.push({-dis[v],v});
                        pre[v]=i;
                    }
                }
            }
            if(dis[sink]==MC) break;
            rep(i,1,n) h[i] += dis[i];
            F mf = mx_flow;
            for(int i=pre[sink];~i;i=pre[e[i].u]) chmin(mf,e[i].c);
            for(int i=pre[sink];~i;i=pre[e[i].u]) e[i].c-=mf, e[i^1].c+=mf;
            mx_flow -= mf;
            flow += mf;
            cost += mf*h[sink];
        }
        return {cost,flow};
    }
    // calculate distance on residual graph
    C cal_dis(int n,int st,int ed) 
    {
        static vector<C> dis; 
        dis.assign(n+1,MC);

        static priority_queue<pair<C,int> > q;
        dis[st]=0; q.push({0,st});
        
        while(q.size())
        {
            auto [d,now] = q.top(); q.pop();
            if(d!=-dis[now]) continue;
            for(auto i: to[now])
            {
                int v=e[i].v;
                if(e[i].c>0 && chmin(dis[v],dis[now]+e[i].w+h[now]-h[v])) q.push({-dis[v],v});
            }
        }
        return dis[ed] + h[ed] - h[st];
    };
}