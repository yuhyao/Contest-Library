template<class T> struct Cartesian_Tree
{
    array<T,maxn+5> h;
    array<int,maxn+5> ls,rs,sta;
    int n,top;
    void build(int _n,T a[])
    {
        n=_n;
        top=0;
        rep(i,1,n) h[i]=a[i];
        rep(i,1,n) ls[i]=rs[i]=0;
        
        rep(i,1,n)
        {
            int k=top;
            while(k>0 && h[sta[k]]>h[i]) k--;
            if(k) rs[sta[k]]=i; 
            if(k<top) ls[i]=sta[k+1];
            sta[++k]=i;
            top=k;
        }
    }
};