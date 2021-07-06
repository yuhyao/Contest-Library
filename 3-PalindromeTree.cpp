#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define maxn 300000
using namespace std;
typedef long long ll;
ll ans=0;
struct Palin_tree
{
    char s[maxn+5];//idx starts from 1.
    int nxt[maxn+5][26],fail[maxn+5],len[maxn+5],cnt[maxn+5];
    int tot,last;
    int newnode(int l)
    {
        memset(nxt[tot],0,sizeof nxt[tot]);
        cnt[tot]=0;
        len[tot]=l;
        return tot++;
    }
    void init()
    {
        tot=0;last=1;
        newnode(0);newnode(-1);
        fail[0]=fail[1]=1;
    }
    int getfail(int x,int l)
    {
        while(s[l-1-len[x]]!=s[l]) x=fail[x];
        return x;
    }
    int ins(int pos)
    {
        int c=s[pos]-'a';
        int p=getfail(last,pos);
        if(!nxt[p][c])
        {
            int q=newnode(len[p]+2);
            fail[q]=nxt[getfail(fail[p],pos)][c];
            nxt[p][c]=q;
        }
        p=nxt[p][c];
        cnt[p]++;
        return last=p;
    }
    void cal()
    {
        per(i,2,tot-1) cnt[fail[i]]+=cnt[i];
        rep(i,2,tot-1) ans=max(ans,1ll*len[i]*cnt[i]);
    }
}pt;

int main()
{
    pt.init();
    scanf("%s",pt.s+1);
    int n=strlen(pt.s+1);
    rep(i,1,n) pt.ins(i);
    ans=0;
    pt.cal();
    printf("%lld\n",ans);
    return 0;
}
