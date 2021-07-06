const int maxn=1000100;
int c,n,tot,qc,kx;
int tr[4*maxn][2];
int ll[maxn],rr[maxn];
pair<int,int> ls[3*maxn];
bool flag[maxn];


void change(int x,int y,int ys,int l,int r,int now){
    if ((x<=l) && (r<=y)) {tr[now][0]=ys;tr[now][1]=true;return;}
    int mid=(l+r)/2;
    if (tr[now][1]){
        change(mid+1,r,tr[now][0],mid+1,r,now*2+1);
        change(l,mid,tr[now][0],l,mid,now*2);
        tr[now][1]=false;
        tr[now][0]=0;
    }
    if (x>=mid+1) change(x,y,ys,mid+1,r,now*2+1);
        else if (y<=mid) change(x,y,ys,l,mid,now*2);
                else {change(mid+1,y,ys,mid+1,r,now*2+1);change(x,mid,ys,l,mid,now*2);}
}

void ask(int x,int y,int l,int r,int now){
    if ((x<=l) && (r<=y) && tr[now][0]>0) {flag[tr[now][0]]=true;return;}
    if (x==y) return;
    int mid=(l+r)/2;
    if (tr[now][1]){
            change(mid+1,r,tr[now][0],mid+1,r,now*2+1);
            change(l,mid,tr[now][0],l,mid,now*2);
            tr[now][1]=false;
            tr[now][0]=0;
        }
    if (x>=mid+1) ask(x,y,mid+1,r,now*2+1);
            else if (y<=mid) ask(x,y,l,mid,now*2);
                    else {ask(mid+1,y,mid+1,r,now*2+1);ask(x,mid,l,mid,now*2);}
}

