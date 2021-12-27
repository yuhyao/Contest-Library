// Note: need more test since it has been modified.
struct Persistent_segtree
{
    #define MAXN (maxn*4+MAXQ*(__lg(maxn)+1))
    int tot;
    array<int,MAXN+5> ls,rs,cnt;

    int clone(int now)
    {
        ++tot;
        ls[tot] = ls[now];
        rs[tot] = rs[now];
        cnt[tot] = cnt[now];
        return tot;
    }
    void init() {tot=0;}
    void upd(int &now,int l,int r,int v) // a[v]++, where v \in [1,n].
    {
        now = clone(now); cnt[now]++;
        if(l==r) return;
        int mid=(l+r)>>1;
        if(v<=mid) upd(ls[now],l,mid,v);
        else upd(rs[now],mid+1,r,v);
    }
    // Call: ask(rt[t],1,n,ql,qr).
    // Return: sum_{ql<=i<=qr} a[i] between time [1,t].
    int ask(int now,int l,int r,int ql,int qr) 
    {
        if(now==0 || r<ql || qr<l) return 0;
        if(ql<=l && r<=qr) return cnt[now];
        int mid=(l+r)>>1;
        return ask(ls[now],l,mid,ql,qr)+ask(rs[now],mid+1,r,ql,qr);
    }
    // Call: find_kth(rt[b],rt[e],1,n,k).
    // Return: the smallest v s.t. sum_{i<=v} a[i] is at least k. 
    // i.e. the k-th smallest value between time [b+1, e].
    int find_kth(int x,int y,int l,int r,int k) 
    {
        if(l==r) return l;
        int mid=(l+r)>>1;
        int C=cnt[ls[y]]-cnt[ls[x]];
        if(k<=C) return find_kth(ls[x],ls[y],l,mid,k);
        else return find_kth(rs[x],rs[y],mid+1,r,k-C);
    }
    #undef MAXN
}pseg;