struct AC
{
    #define C 26
    int next[maxn+5][C],fail[maxn+5],cnt[maxn+5];
    int tot,root;
    int newnode()
    {
        tot++;
        memset(next[tot],0,sizeof next[tot]);
        fail[tot]=0;
        cnt[tot]=0;
        return tot;
    }
    void init()
    {
        tot=0;
        root=newnode();
    }
    void insert(string &s)
    {
        int now=root,l=s.length();
        rep(i,0,l-1)
        {
            int c=s[i]-'a';
            if(next[now][c]==0) next[now][c]=newnode();
            now=next[now][c];
        }
        cnt[now]++;
    }
    void build()
    {
        queue<int> q; q.push(root);
        rep(i,0,C-1) next[0][i]=root;
        while(q.size())
        {
            int now=q.front(); q.pop();
            rep(i,0,C-1)
            {
                if(next[now][i]==0) next[now][i]=next[fail[now]][i];
                else fail[next[now][i]]=next[fail[now]][i], q.push(next[now][i]);
            }
            cnt[now]+=cnt[fail[now]];
        }
    }
    ll query(string &s)
    {
        int now=root,l=s.length();
        ll sum=0;
        rep(i,0,l-1)
        {
            now=next[now][s[i]-'a'];
            sum+=cnt[now];
        }
        return sum;
    }
    #undef C
}ac;