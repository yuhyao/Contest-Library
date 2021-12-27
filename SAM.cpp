struct SAM
{
    // maxn should be the maximum length of the string.
    // l -> length of the longest substring corresponding to the state.
    // fa -> father in the reverse suffic tree. Note that fa[i]<i doesn't hold.
    array<int,maxn*2+5> fa,l,right;
    int nxt[maxn*2+5][26];
    int last,tot,N;
    int newnode()
    {
        tot++;
        memset(nxt[tot],0,sizeof nxt[tot]);
        right[tot]=0;
        return tot;
    }
    void init()
    {
        tot=N=0;
        last=newnode();
        fa[last]=l[last]=0;
    }
    void extend(char ch)
    {
        N++;
        int c=ch-'a'; // change here if we use Capitals.
        int p=last,np;
        last=np=newnode();
        l[np]=l[p]+1;
        right[np]=1;
        while(p && !nxt[p][c]) nxt[p][c]=np,p=fa[p];
        if(!p) fa[np]=1;
        else
        {
            int q=nxt[p][c];
            if(l[q]==l[p]+1) fa[np]=q;
            else
            {
                int nq=newnode();
                l[nq]=l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof nxt[q]);
                fa[nq]=fa[q];
                fa[np]=fa[q]=nq;
                while(p && nxt[p][c]==q) nxt[p][c]=nq,p=fa[p];
            }
        }
    }
    // After doing the following, right[st] <-> number of occurrence.
    void cal()
    {
        vi sum(N+1,0),q(tot+1);
        rep(i,2,tot) sum[l[i]]++;
        rep(i,1,N) sum[i]+=sum[i-1];
        rep(i,2,tot) q[sum[l[i]]--]=i; // not include root.
        per(i,1,tot-1) right[fa[q[i]]]+=right[q[i]];
    }
}sam;