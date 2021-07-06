const int maxn=5000;
int n,x,y,fore,rear,cnt,ans,father[maxn],f[maxn],
path[maxn],tra[maxn],que[maxn],match[maxn];
bool a[maxn][maxn],check[maxn],treec[maxn],pathc[maxn];

inline void push(int x){
    que[++rear]=x;
    check[x]=true;
    if(!treec[x]){
        tra[++cnt]=x;
        treec[x]=true;
    }
}
