int fail[maxn+5]; // equivalent to border.
// indices start from 0.
void calfail(char *p)
{
    int l=strlen(p),j=0;
    fail[0]=0;
    rep(i,1,l-1)
    {
        while(j && p[j]!=p[i]) j=fail[j-1];
        if(p[j]==p[i]) j++;
        fail[i]=j;
    }
}
vi kmp(char *p,char *t) // gets all matched positions.
{
    int n=strlen(t),m=strlen(p),j=0;
    vi match(n,0);
    rep(i,0,n-1)
    {
        while(j && (j==m || p[j]!=t[i])) j=fail[j-1];
        if(p[j]==t[i]) j++;
        match[i]=(j==m);
    }
    return match;
}