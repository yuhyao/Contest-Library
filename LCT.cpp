// Maintain each component as a rooted tree. For each vertex we mark at most one child as preferred child.
// Edge between a vertex and its preferred child is called preferred edge. 
// - Preferred edges form preferred paths.
// Each preferred path is represented as an auxiliary tree (a splay). 
// - The key of a node is just the depth of the corresponding vertex in the rooted tree.
struct LCT
{    
    #define ls(x) son[x][0]
    #define rs(x) son[x][1]
    //vsz is the size of virtual subtree, sz is the size of subtree.
    int fa[maxn+5],son[maxn+5][2],sz[maxn+5],vsz[maxn+5];
    bool rev[maxn+5];
    void init(int n)
    {
        sz[0]=vsz[0]=0;
        rep(i,1,n) rev[i]=0;
        rep(i,1,n) sz[i]=1;
        rep(i,1,n) vsz[i]=0;
        rep(i,1,n) fa[i]=son[i][0]=son[i][1]=0;
    }
    void push_rev(int x)
    {
        if(!x) return;
        rev[x] ^= 1;
        swap(ls(x),rs(x));
    }
    void pushup(int x)
    {
        sz[x]=sz[ls(x)]+sz[rs(x)]+1+vsz[x]; //subtree info
    }
    void pushdown(int x)
    {   // pushdown before you enter a child!
        if(rev[x]) 
        {
            push_rev(ls(x));
            push_rev(rs(x));
            rev[x] = 0;
        }
    }
    bool isrt(int x)
    {   // chech if x is the root of the splay it is in.
        return ls(fa[x])!=x && rs(fa[x])!=x;
    }
    void rot(int x)
    {
        int y=fa[x],z=fa[y];
        int l=rs(y)==x,r=l^1;
        if(!isrt(y)) son[z][rs(z)==y]=x;
        fa[son[x][r]]=y;
        fa[y]=x; fa[x]=z;
        son[y][l]=son[x][r]; son[x][r]=y;
        pushup(y);
    }
    stack<int> sta;
    void splay(int x)
    {   // make x the root of the splay it is in.
        sta.push(x);
        for(int i=x;!isrt(i);i=fa[i]) sta.push(fa[i]);
        while(sz(sta)) pushdown(sta.top()), sta.pop();
        while(!isrt(x))
        {
            int y=fa[x],z=fa[y];
            if(!isrt(y))
            {
                if((ls(y)==x) ^ (ls(z)==y)) rot(x);
                else rot(y);
            }
            rot(x);
        }
        pushup(x);
    }
    void access(int x)
    {   // Say y is the current root of the component (the rooted tree),
        // then we make the path y - ... - x a preferred path.
        // - Note: it's possible that neither x or y is the root of the splay after this 'access'.
        for(int l=0;x;l=x,x=fa[x])
        {
            splay(x); // move x to the root of the cuurent splay.
            vsz[x]+=sz[rs(x)]; // rs(x) becomes a non-preferred child of x.
            vsz[x]-=sz[l]; // l becomes a preferred child of x.
            rs(x)=l; // make l be the preferred child of x.
            pushup(x); // update info.
        }
    }
    int findrt(int x)
    {   // return the root of the component.
        access(x); splay(x);
        while(ls(x)) pushdown(x), x=ls(x);
        return x;
    }
    void reroot(int x)
    {   // Make x be the root in the component. 
        // x also becomes the root of the splay.
        access(x); splay(x); rev[x]^=1;
    }
    void link(int x,int y)
    {   // link x to y, i.e. make x be a (non-preferred) child of y.
        reroot(x); fa[x]=y;
        reroot(y); vsz[y]+=sz[x]; // We don't make (y,x) a preferred edge here.
        pushup(y);
    }
    int cut(int x,int y)
    {   // Say x - ... - u - y, then we cut (u,y) and return u.
        reroot(x);access(y);splay(y);
        int l=ls(y);
        ls(y)=fa[l]=0;
        pushup(y);
        while(rs(l)) pushdown(l),l=rs(l);
        return l;
    }
}tr;