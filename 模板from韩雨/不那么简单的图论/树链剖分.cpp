const int maxn=100000+5;
const int maxm=maxn+maxn;
int v[maxm],Prev[maxm],info[maxn],Q[maxn],idx[maxn],dep[maxn],size[maxn],belong[maxn],father[maxn];
bool vis[maxn];
int head[maxn],len[maxn];
int l,r,ans,cnt=0;
int N,nedge =0;
inline void insert(int x,int y){
    ++nedge;
    v[nedge]=y;Prev[nedge]=info[x];info[x]=nedge;
}

void split(){
    memset(dep,-1,sizeof(dep));
    l=0;
    dep[Q[r=1]=1]=0;
    father[1]=-1;
    while (l<r) {
        int x=Q[++l];
        vis[x]=false;
        for (int y=info[x];y;y=Prev[y])
            if (dep[v[y]]==-1){
                dep[Q[++r]=v[y]]=dep[x]+1;
                father[v[y]]=x;
            }
    }
    for (int i=r;i;--i){
        int x=Q[i],p=-1;
        size[x]=1;
        for (int y=info[x];y;y=Prev[y])
            if (vis[v[y]]){
                size[x]+=size[v[y]];
                if (p==-1 || size[v[y]]>size[p])
                    p=v[y];
            }
        if (p==-1){
            idx[x]=len[++cnt]=1;
            belong[head[cnt]=x]=cnt;
        }
        else {
            idx[x]=++len[belong[x]=belong[p]];
            head[belong[x]]=x;
        }
        vis[x]=true;
    }
}
