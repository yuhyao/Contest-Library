struct Aho_Corasick
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
        while(q.size())
        {
            int now=q.front(); q.pop();
            rep(i,0,C-1)
            {
                int son=next[now][i];
                if(son)
                {
                    int p=fail[now];
                    while(p && !next[p][i]) p=fail[p];
                    fail[son]=p?next[p][i]:root;
                    q.push(son);
                }
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
            int c=s[i]-'a';
            while(now && !next[now][c]) now=fail[now];
            now=now?next[now][c]:root;
            sum+=cnt[now];
        }
        return sum;
    }
    #undef C
}ac;