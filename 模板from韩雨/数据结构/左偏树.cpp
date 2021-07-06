const int maxn=100000;
int tot,v[maxn],l[maxn],r[maxn],d[maxn];
int merge(int x,int y)
{
    int t;
    if (!x) return y;
    if (!y) return x;
    if (v[x]>v[y]) {t=x;x=y;y=t;}
    r[x]=merge(r[x],y);
    if (d[l[x]]<d[r[x]]) {t=l[x];l[x]=r[x];r[x]=t;}
    d[x]=d[r[x]]+1;
    return (x);        
} 

int init(int x)
{
    ++tot;
    v[tot]=x;
    l[tot]=r[tot]=d[tot]=0;
    return tot;
}

int insert(int x,int y)
{
    return (merge(x,init(y)));
}

int top (int x)
{
    return (v[x]);
}

int pop(int x)
{
    return (merge(l[x],r[x]));
}
