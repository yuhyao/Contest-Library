struct Hopcroft
{
    // indices start from 1.
    int n1,n2; // n1=size of X, n2=size of Y.
    vi e[maxn+5]; // from X part to Y part.
    int match_x[maxn+5],match_y[maxn+5]; // record the matched vertex for each vertex on both sides.
    queue<int> q;
    int dx[maxn+5],dy[maxn+5];
    bool vis[maxn+5];
    
    void init(int _n1,int _n2)
    {
        n1=_n1, n2=_n2;
        rep(i,1,n1) e[i].clear();
    }

    bool find(int x)
    {
        for(auto y: e[x]) if(vis[y]==0 && dy[y]==dx[x]+1)
        {
            vis[y]=1;
            if(match_y[y]==0 || find(match_y[y]))
            {
                match_x[x]=y;
                match_y[y]=x;
                return 1;
            }
        }
        return 0;
    }
    int work()
    {
        rep(i,1,n1) match_x[i]=0;
        rep(i,1,n2) match_y[i]=0;
        int ans=0;
        while(1)
        {
            bool ok=0;
            while(q.size()) q.pop();
            rep(i,1,n1) dx[i]=0;
            rep(i,1,n2) dy[i]=0;
            rep(i,1,n1) if(match_x[i]==0) q.push(i);
            while(q.size())
            {
                int x=q.front(); q.pop();
                for(auto y: e[x]) if(dy[y]==0)
                {
                    dy[y]=dx[x]+1;
                    if(match_y[y])
                    {
                        dx[match_y[y]]=dy[y]+1;
                        q.push(match_y[y]);
                    }
                    else ok=1;
                }
            }
            if(ok==0) break;
            rep(i,1,n2) vis[i]=0;
            rep(i,1,n1) if(match_x[i]==0 && find(i)) ans++;
        }
        return ans;
    }
}hp;
