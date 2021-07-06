#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 100000
#define ls(x) son[x][0]
#define rs(x) son[x][1]
using namespace std;
struct LCT
{
    //vsz是虚子树大小和, sz是总子树大小和.
    int fa[maxn+5],son[maxn+5][2],sz[maxn+5],vsz[maxn+5];
    bool rev[maxn+5];
    int q[maxn+5],top;
    void init(int n)
    {
        sz[0]=vsz[0]=0;
        rep(i,1,n) rev[i]=0;
        rep(i,1,n) sz[i]=1;
        rep(i,1,n) vsz[i]=0;
        rep(i,1,n) fa[i]=son[i][0]=son[i][1]=0;
    }
    bool isrt(int x)
    {
        return ls(fa[x])!=x && rs(fa[x])!=x;
    }
    void pushup(int x)
    {
        sz[x]=sz[ls(x)]+sz[rs(x)]+1+vsz[x];//subtree info
    }
    void pushdown(int x)
    {
        if(!rev[x]) return;
        rev[x]=0;
        rev[ls(x)]^=1;
        rev[rs(x)]^=1;
        swap(ls(x),rs(x));
    }
    void rot(int x)
    {
        int y=fa[x],z=fa[y];
        int l=rs(y)==x,r=l^1;
        if(!isrt(y)) son[z][rs(z)==y]=x;
        fa[son[x][r]]=y;
        fa[y]=x;fa[x]=z;
        son[y][l]=son[x][r];son[x][r]=y;
        pushup(y);
    }
    void splay(int x)
    {
        q[++top]=x;
        for(int i=x;!isrt(i);i=fa[i]) q[++top]=fa[i];
        while(top) pushdown(q[top--]);
        while(!isrt(x))
        {
            int y=fa[x],z=fa[y];
            if(!isrt(y))
            {
                if(ls(y)==x ^ ls(z)==y) rot(x);
                else rot(y);
            }
            rot(x);
        }
        pushup(x);
    }
    void access(int x)
    {
        for(int l=0;x;l=x,x=fa[x])
        {
            splay(x);
            vsz[x]+=sz[rs(x)]-sz[l];//subtree info
            rs(x)=l;pushup(x);
        }
    }

    int findrt(int x)
    {
        access(x);splay(x);
        while(pushdown(x),ls(x)) x=ls(x);
        return x;
    }
    void reroot(int x)
    {
        access(x);splay(x);rev[x]^=1;
    }
    void link(int x,int y)
    {
        reroot(x);fa[x]=y;
        int t=findrt(y);
        reroot(y);vsz[y]+=sz[x];pushup(y);//subtree info
        reroot(t);
    }
    int cut(int x,int y)
    {
        reroot(x);access(y);splay(y);
        int l=ls(y);
        ls(y)=fa[l]=0;
        pushup(y);
        while(pushdown(l),rs(l)) l=rs(l);
        return l;
    }
}tr;
int main()
{
    return 0;
}
