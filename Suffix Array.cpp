struct SA
{
    int n,sa[maxn+5],rk[maxn+5],h[maxn+5],ps[maxn+5],tmp[maxn+5];
    char *a;
    int lg[maxn+5],st[20][maxn+5];
    void RSort(int n,int m)
    {
        rep(i,0,m) ps[i]=0;
        rep(i,1,n) ps[rk[tmp[i]]]++;
        rep(i,1,m) ps[i]+=ps[i-1];
        per(i,1,n) sa[ps[rk[tmp[i]]]--]=tmp[i];
    }
    bool cmp(int *f,int x,int y,int w,int n)
    {
        if(x+w>n || y+w>n) return 0;
        return f[x]==f[y] && f[x+w]==f[y+w];
    }
    // h[i] = lcp(suff[sa[i-1]],suff[sa[i]]);
    void cal_height()
    {
        for(int i=1,k=0;i<=n;h[rk[i++]]=k)
            for(k=k?k-1:k;a[i+k]==a[sa[rk[i]-1]+k];k++);
        // calculate sparse table for lcp.
        rep(i,2,n) lg[i]=lg[i>>1]+1;
        rep(j,1,n) st[0][j]=h[j];
        rep(i,1,lg[n]) rep(j,1,n-(1<<i)+1) st[i][j]=min(st[i-1][j],st[i-1][j+(1<<(i-1))]);
    }
    // index of a starts from 1, characters should be in [0,m].
    void build(char *s,int _n,int m=127) 
    {
        a=s; n=_n;
        rep(i,1,n) rk[i]=a[i];
        rep(i,1,n) tmp[i]=i;
        RSort(n,m);
        for(int j=1,p=1;p<n;j<<=1,m=p)
        {
            p=0;
            rep(i,n-j+1,n) tmp[++p]=i;
            rep(i,1,n) if(sa[i]>j) tmp[++p]=sa[i]-j;
            RSort(n,m);
            rep(i,1,n) swap(rk[i],tmp[i]);
            rk[sa[1]]=p=1;
            rep(i,2,n) rk[sa[i]]=cmp(tmp,sa[i],sa[i-1],j,n)?p:++p;
        }
        cal_height();
    }
    int lcp(int i,int j) // return lcp(suff[i],suff[j])
    {
        int l=rk[i],r=rk[j];
        if(l>r) swap(l,r);
        l++;
        int k=lg[r-l+1];
        return min(st[k][l],st[k][r-(1<<k)+1]);
    }
}sa;


/*
Q1：一个串中不可重叠的重复最长子串是多长？
A1：二分答案。设验证答案k，分组验证，再判断每组中最大的sa值和最小的sa值相差是否大于等于k，有一组超过的话k就是合法答案。

Q2：一个字符串不相等的子串的个数是多少？
A2：每个子串一定是某个后缀的前缀，那么原问题等价于求所有后缀之间的不相同的前缀的个数。而且可以发现每一个后缀Suffix[sa[i]]的贡献是Len - sa[i] + 1,但是有子串算重复，重复的就是Heigh[i]个与前面相同的前缀，那么减去就可以了。最后，一个后缀Suffix[sa[i]]的贡献就是Len - sa[k] + 1 - Height[k]。

Q3：给定两个字符串A和B，求长度不小于k的公共子串的个数(可以相同)？
A3：求出后缀数组后利用单调栈维护来统计。

Q4:求n个字符串的最长公共子串?
A4:二分答案。将n个串拼起来，分组验证，注意拼串时插入的新字符是否会造成影响（只插入n-1个新字符的话就没影响）。
*/
