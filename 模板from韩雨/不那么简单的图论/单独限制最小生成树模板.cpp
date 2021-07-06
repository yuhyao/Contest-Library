#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;

const int inf=1000000000;
const int maxn=300000;
int a[2*maxn],b[2*maxn],c[2*maxn],order[2*maxn],adj[2*maxn];
int parent[maxn],to[maxn],best[maxn],candidate[maxn],nextedge[2*maxn],firstedge[2*maxn];
bool choose[2*maxn];

bool compare(int i,int j){ return c[i]<c[j];}

int findRoot(int i){
    if (parent[i]i){
        parent[i]=findRoot(parent[i]);
    }
    return parent[i];
}

void addEdge(int i,int u,int v){
    to[i]=v;
    nextedge[i]=firstedge[u];
    firstedge[u]=i;
}

void dfs(int p,int u){
    for (int iter=firstedge[u];iter-1;iter=nextedge[iter]){
        if (!choose[iter>>1]){
            continue;
        }
        int v=to[iter];
        if (p==v){
            continue;
        }
        if (u){
            best[v]=c[iter>>1];
            candidate[v]=iter>>1;
            if (best[u]>best[v]){
                best[v]=best[u];
                candidate[v]=candidate[u];
            }
        }    else {
            best[v]=-inf;
        }
        dfs(u,v);
    }
}

void myAddEdge(int i){
    addEdge(i+i,a[i],b[i]);
    addEdge(i+i+1,b[i],a[i]);
}

vector <int> restricted_mst(int n,int limit,vector<pair<pair<int,int>,int>> &edges){
    int m=(int) edges.size();
    for (int i=0;i<m;++i){
        a[i]=edges[i].first.first;
        b[i]=edges[i].first.second;
        c[i]=edges[i].second;
        if (a[i]>b[i]) swap(a[i],b[i]);
        order[i]=i;
    }
    sort(order,order+m,compare);
    for (int i=0;i<n;++i){
        parent[i]=i;
    }
    memset(choose,0,sizeof(choose));
    for (int i=0;i<m;++i){
        int e=order[i];
        if (!a[e] || findRoot(a[e]) == findRoot(b[e])){
            continue;
        }
        choose[e]=true;
        parent[findRoot(a[e])]=findRoot(b[e]);
    }
    int component=0;
    for (int i=1;i<n;++i){
        if (findRoot(i)==i){
            component++;
            best[i]=inf;
        }
    }
    if (component>limit){
        return vector<int> (1,-1);
    }
    memset(adj,-1,sizeof(adj));
    for (int i=0;i<m;++i){
        if (a[i]){
            continue;
        }
        adj[b[i]]=i;
        int r=findRoot(b[i]);
        if (c[i]<best[r]){
            best[r]=c[i];
            candidate[r]=i;
        }
    }
    for (int i=1;i<n;++i){
        if (findRoot(i)==i){
            if(best[i]==inf){
                return vector<int> (1,-1);
            }
            choose[candidate[i]]=true;
        }
    }
    memset(firstedge,-1,sizeof(firstedge));
    for (int i=0;i<m;++i){
        if (choose[i]){
            myAddEdge(i);
        }
    }
    while (component<limit){
        dfs(-1,0);
        int tmpBest=inf,tmpCandidate;
        for (int i=1;i<n;++i){
            if (adj[i]==-1 || best[i]==-inf){
                continue;
            }
            if (c[adj[i]]-best[i]<tmpBest){
                tmpBest=c[adj[i]]-best[i];
                tmpCandidate=i;
            }
        }
        if (tmpBest==inf){
            return vector<int> (1,-1);
        }
        choose[candidate[tmpCandidate]]=false;
        choose[adj[tmpCandidate]]=true;
        myAddEdge(adj[tmpCandidate]);
        ++component;
    }
    vector <int> result;
    for (int i=0;i<m;++i)
        if (choose[i]) result.push_back(i);
    return result;
}

int main(){
    
}
