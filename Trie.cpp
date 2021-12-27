struct trie
{
    #define C 26
    #define MAXN (maxn*30)
    int next[MAXN+5][C];
    array<int,MAXN+5> cnt;
    int tot,root;
    int newnode()
    {
        cnt[++tot]=0;
        memset(next[tot],0,sizeof next[tot]);
        return tot;
    }
    void init()
    {
        tot=0;
        root=newnode();
    }
    void ins(char *s)
    {
        int l=strlen(s),p=root;
        rep(i,0,l-1)
        {
            int id=s[i]-'a';
            if(!next[p][id]) next[p][id]=newnode();
            p=next[p][id];
        }
        cnt[p]++;
    }
    int check(char *s)
    {
        int l=strlen(s),p=root;
        rep(i,0,l-1)
        {
            int id=s[i]-'a';
            if(!next[p][id]) return 0;
            p=next[p][id];
        }
        return cnt[p];
    }
    #undef C
    #undef MAXN
}t;
