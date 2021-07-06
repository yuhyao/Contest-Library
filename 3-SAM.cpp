#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define maxn 500000
using namespace std;
char str[maxn+5];
int q[maxn*2+5];
int sum[maxn+5];
int n;
struct SAM
{
    // maxn should be the maximum length of the string.
    array<int,maxn*2+5> fa,l,right;
    int nxt[maxn*2+5][26];
    int last,tot;
    int newnode()
    {
        tot++;
        memset(nxt[tot],0,sizeof nxt[tot]);
        right[tot]=0;
        return tot;
    }
    void init()
    {
        tot=0;
        last=newnode();
        fa[last]=l[last]=0;
    }
    void extend(char ch)
    {
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
    void cal()
    {
        // remember to clear the array: sum.
        rep(i,2,tot) sum[l[i]]++;
        rep(i,1,n) sum[i]+=sum[i-1];
        rep(i,2,tot) q[sum[l[i]]--]=i; // not include root.
        per(i,1,tot-1) right[fa[q[i]]]+=right[q[i]];
    }
}sam;

int main()
{
    scanf("%s",str);
    n=strlen(str);
    sam.init();
    per(i,0,n-1) sam.add(str[i]);
    fill(sum,sum+n+2,0);
    sam.cal();
    return 0;
}
