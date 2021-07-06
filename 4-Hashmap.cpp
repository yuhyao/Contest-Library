#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define pb push_back
#define mp make_pair
#define FI first
#define SE second
#define maxn 2000000
#define mod 1000000007
#define inf 0x3f3f3f3f
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef double db;

typedef unsigned long long hashv;

const int HASH=9999991;

struct HASHMAP
{
    int head[HASH],next[maxn+5],tot;
    hashv state[maxn+5];
    int f[maxn+5];
    void init()
    {
        tot=0;
        memset(head,-1,sizeof(head));
    }
    void add(hashv val)
    {
        int h=val%HASH;
        for(int i=head[h];i!=-1;i=next[i]) if(val==state[i])
        {
            f[i]++;
            return;
        }
        f[tot]=1;
        state[tot]=val;
        next[tot]=head[h];
        head[h]=tot++;
    }
    int ask(hashv val)
    {
        int h=val%HASH;
        for(int i=head[h];i!=-1;i=next[i]) if(val==state[i]) return f[i];
        return 0;
    }
    int operator [](const hashv &x) {return ask(x);}
}H;

int main()
{
    H.init();
    return 0;
}
