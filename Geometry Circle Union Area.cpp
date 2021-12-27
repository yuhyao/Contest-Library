struct P
{
    db x,y;
    db angle;
    int d;
    P():x(0),y(0){}
    P(db a,db b):x(a),y(b){}
    void in() {scanf("%lf%lf",&x,&y);}
    P operator +(const P &a) const {return P(x+a.x,y+a.y);}
    P operator -(const P &a) const {return P(x-a.x,y-a.y);}
    P operator *(const db &a) const {return P(x*a,y*a);}
    P operator /(const db &a) const {return P(x/a,y/a);}
    db norm() {return sqrt(x*x+y*y);}
};
typedef vector<P> vp;

db dot(P a,P b) {return a.x*b.x+a.y*b.y;}
db cross(P a,P b) {return a.x*b.y-a.y*b.x;}

P c[maxn+5];
db r[maxn+5];
db area[maxn+5];

bool Gcmp(P a,P b)
{
    if(cmp(a.angle-b.angle)!=0) return a.angle<b.angle;
    return a.d>b.d;
}
db myacos(db x)
{
    if(x<-1) x=-1;
    if(x>1) x=1;
    return acos(x);
}
db cal(int n)
{
    rep(i,1,n) area[i]=0;
    rep(i,1,n)
    {
        int b=0,cnt=0;
        vp vec;
        db R=r[i];
        rep(j,1,n)
        {
            db d=(c[i]-c[j]).norm();
            db r1=r[i],r2=r[j];
            if(cmp(d-r1-r2)>=0) continue;
            if(cmp(r2-r1-d)>=0) {b++;continue;}
            if(cmp(r1-r2-d)>=0) continue;
            P li=c[j]-c[i];
            db s0=atan2(li.y,li.x);
            db sita=myacos((d*d+r1*r1-r2*r2)/(2*d*r1));
            db s1=s0-sita;
            db s2=s0+sita;
            P p1=c[i]+P(r1*cos(s1),r1*sin(s1)); p1.d=1; p1.angle=atan2(r1*sin(s1),r1*cos(s1));
            P p2=c[i]+P(r1*cos(s2),r1*sin(s2)); p2.d=-1; p2.angle=atan2(r1*sin(s2),r1*cos(s2));
            if(cmp(p1.angle-p2.angle)>=0) cnt++;
            vec.pb(p1);
            vec.pb(p2);
        }
        P p1=c[i]+P(-R,0); p1.d=cnt; p1.angle=-pi;
        P p2=c[i]+P(-R,0); p2.d=-cnt; p2.angle=pi;
        vec.pb(p1);
        vec.pb(p2);
        sort(vec.begin(),vec.end(),Gcmp);
        int l=vec.size();
        rep(k,0,l-2)
        {
            b+=vec[k].d;
            area[b] += ((vec[k+1].angle-vec[k].angle)*R*R - cross(vec[k]-c[i],vec[k+1]-c[i]) + cross(vec[k],vec[k+1]))/2.0;
        }
    }
    return area[1];
}

int main()
{
    int T; scanf("%d",&T);
    while(T--)
    {
        int n; scanf("%d",&n);
        rep(i,1,n) c[i].in(),scanf("%lf",&r[i]);
        db A=cal(n);
        printf("%.10f\n",A);
    }
    return 0;
}
