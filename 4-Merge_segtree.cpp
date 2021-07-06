namespace merge_segtree 
{
   struct node
    {
        ll a,tag;
        node *ls,*rs;
        node() {a=tag=0; ls=rs=NULL;}
    };
    void push(node *t,ll x)
    {
        t->a+=x; t->tag+=x;
    }
    void pu(node *t)
    {
        t->a=min(t->ls?t->ls->a:1ll<<60,t->rs?t->rs->a:1ll<<60);
    }
    void pd(node *t)
    {
        if(t->tag)
        {
            if(t->ls) push(t->ls,t->tag);
            if(t->rs) push(t->rs,t->tag);
            t->tag=0;
        }
    }
    void chg(node* &t,int l,int r,int p,ll x)
    {
        if(t==NULL) t=new node;
        if(l==r)
        {
            t->a=x;
            return;
        }
        pd(t);
        int mid=(l+r)>>1;
        if(p<=mid) chg(t->ls,l,mid,p,x);
        else chg(t->rs,mid+1,r,p,x);
        pu(t);
    }
    ll ask(node *t,int l,int r,int p)
    {
        if(l==r || t==NULL) return t?t->a:1ll<<60;
        pd(t);
        int mid=(l+r)>>1;
        if(p<=mid) return ask(t->ls,l,mid,p);
        else return ask(t->rs,mid+1,r,p);
    }
    node* merge(node* t1,node*t2)
    {
        if(t1==NULL) return t2; 
        if(t2==NULL) return t1; 
        pd(t1);
        pd(t2);
        t1->a=min(t1->a,t2->a);
        t1->ls=merge(t1->ls,t2->ls);
        t1->rs=merge(t1->rs,t2->rs);
        delete(t2);
        return t1;
    }
}