int lcp[maxn+5],extend[maxn+5];
void get_lcp(char* p)
{
    int m=strlen(p),p0=0,r=-1;
    lcp[0]=m;
    rep(k,0,m-2)
    {
        if(r>k && r-k>lcp[k+1-p0]) lcp[k+1]=lcp[k+1-p0];
        else
        {
            int i;
            for(i=max(k,r);p[i+1]==p[i-k];i++);
            lcp[k+1]=i-k;
            if(i>r) r=i,p0=k+1;
        }
    }
    return;
}
void get_ext(char* t,char* p)
{
    int n=strlen(t),m=strlen(p),p0=0,r=-1;
    rep(k,-1,n-2)
    {
        if(r>k && r-k>lcp[k+1-p0]) extend[k+1]=lcp[k+1-p0];
        else
        {
            int i;
            for(i=max(k,r);t[i+1]==p[i-k] && p[i-k];i++);
            extend[k+1]=i-k;
            if(i>r) r=i,p0=k+1;
        }
    }
    return;
}