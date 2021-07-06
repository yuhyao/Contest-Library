template<class T> struct BIT
{
    int n;
    T a[maxn+5];
    void init(int _n)
    {
        n=_n;
        rep(i,1,n) a[i]=0;
    }
    void add(int i,T x)
    {
        for(;i<=n;i+=i&-i) a[i]+=x;
    }
    T ask(int i)
    {
        T ans=0;
        for(;i;i-=i&-i) ans+=a[i];
        return ans;
    }
    void add(int l,int r,T x) {add(l,x); add(r+1,-x);}
    T ask(int l,int r) {return ask(r)-ask(l-1);}
    int find(T x) // find the least number pos such that a[pos] + pos >= x.
    {
        int pos=0;
        per(i,0,31-__builtin_clz(n)) // log_2(n) = 31 - __builtin_clz(n)
        {
            if((pos | (1<<i)) <= n && a[pos | (1<<i)] + (pos | (1<<i)) < x) 
            {
                pos|=1<<i;
                x-=a[pos];
            }
        }
        return pos+1;
    }
};

template<class T> struct BIT2D
{
    int n,m;
    T a[maxn+5][maxn+5];
    void init(int _n,int _m)
    {
        n=_n; m=_m;
        rep(i,1,n) rep(j,1,m) a[i][j]=0;
    }
    void add(int x,int y,T val)
    {
        for(int i=x;i<=n;i+=i&-i) for(int j=y;j<=m;j+=j&-j) a[i][j]+=val;
    }
    T ask(int x,int y)
    {
        T ans=0;
        for(int i=x;i;i-=i&-i) for(int j=y;j;j-=j&-j) ans+=a[i][j];
        return ans;
    }
};
