#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 100000
using namespace std;
int RAND(){return 1ll*rand()*rand();}
struct node
{
    int sz,pri;
    int ls,rs;
}t[maxn+5];
int tot,root;
int newnode()
{
    t[++tot].pri=RAND();
    t[tot].sz=1;
    t[tot].ls=t[tot].rs=0;
    return tot;
}
void init()
{
    root=tot=0;
}
void pu(int i)
{
    t[i].sz=t[t[i].ls].sz+t[t[i].rs].sz+1;
}
int Merge(int x,int y)//x->key < y->key
{
    if(!x || !y) return x|y;
    if(t[x].pri>t[y].pri) {t[x].rs=Merge(t[x].rs,y);pu(x);return x;}
    else {t[y].ls=Merge(x,t[y].ls);pu(y);return y;}
}
void split(int i,int k,int &x,int &y)
{
    if(!i) {x=y=0;return;}
    if(k>=t[t[i].ls].sz+1) {x=i;split(t[i].rs,k-t[t[i].ls].sz-1,t[x].rs,y);}
    else {y=i;split(t[i].ls,k,x,t[y].ls);}
    pu(i);
}
void dfs(int now)
{
    if(!now) return;
    dfs(t[now].ls);
    printf("%d ",now);
    dfs(t[now].rs);
}
int main()
{
    srand(time(NULL));
    int n,m;
    scanf("%d%d",&n,&m);
    init();
    rep(i,1,n)
    {
        newnode();root=Merge(root,i);
    }
    while(m--)
    {
        int L,R;
        scanf("%d%d",&L,&R);
        R=L+R-1;
        int l,mid,r;
        split(root,R,mid,r);
        split(mid,L-1,l,mid);
        root=Merge(l,r);
        root=Merge(mid,root);
    }
    dfs(root);
    puts("");
    return 0;
}
