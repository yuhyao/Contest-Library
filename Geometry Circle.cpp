const db eps=1e-9;
const db pi=acos(-1.0);
int cmp(db x) {return (x>eps)-(x<-eps);}

struct P
{
    db x,y;
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

db mysqrt(db x) {return sqrt(max(0.0,x));}

vp c_c_l(P a,P b,P o,db r)
{
    vp ret;
    db x0=o.x,y0=o.y;
    db x1=a.x,y1=a.y;
    db x2=b.x,y2=b.y;
    db dx=x2-x1,dy=y2-y1;
    db A=dx*dx+dy*dy;
    db B=2*dx*(x1-x0)+2*dy*(y1-y0);
    db C=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)-r*r;
    db delta=B*B-4*A*C;
    if(cmp(delta)>0)
    {
        db t1=(-B-mysqrt(delta))/(2*A);
        db t2=(-B+mysqrt(delta))/(2*A);
        if(cmp(t1-1)<=0 && cmp(t1)>=0) ret.pb(P(x1+t1*dx,y1+t1*dy));
        if(cmp(t2-1)<=0 && cmp(t2)>=0) ret.pb(P(x1+t2*dx,y1+t2*dy));
    }
    return ret;
}
db r;

db sector_area(P a,P b)
{
    db theta=atan2(a.y,a.x)-atan2(b.y,b.x);
    while(theta<=0) theta+=2*pi;
    while(theta>2*pi) theta-=2*pi;
    theta=min(theta,2*pi-theta);
    return r*r*theta/2;
}
db calc(P a,P b)
{
    int ina=cmp(a.norm()-r)<0;
    int inb=cmp(b.norm()-r)<0;
    if(ina)
    {
        if(inb) return fabs(cross(a,b))/2.0;
        else
        {
            vp p=c_c_l(a,b,P(0,0),r);
            return sector_area(b,p[0])+fabs(cross(a,p[0]))/2.0;
        }
    }
    else
    {
        vp p=c_c_l(a,b,P(0,0),r);
        if(inb) return sector_area(p[0],a)+fabs(cross(p[0],b))/2.0;
        else
        {
            if(p.size()==2) return sector_area(a,p[0])+sector_area(p[1],b)+fabs(cross(p[0],p[1]))/2.0;
            else return sector_area(a,b);
        }
    }
}
db area(P res[],int n)
{
    res[n]=res[0];
    db ret=0;
    rep(i,0,n-1)
    {
        int sgn=cmp(cross(res[i],res[i+1]));
        ret+=sgn*calc(res[i],res[i+1]);
    }
    return fabs(ret);
}

P p[maxn+5];
int main()
{
    int n,cas=0;
    db k;
    while(~scanf("%d%lf",&n,&k))
    {
        cas++;
        rep(i,0,n-1) p[i].in();
        P A,B;
        A.in();
        B.in();
        P c=B-A;
        P t1=A+c/(k+1);
        P t2=A+c/(1-k);
        P o=(t1+t2)/2;
        r=(t2-t1).norm()/2;
        rep(i,0,n-1) p[i]=p[i]-o;
        printf("Case %d: %.12f\n",cas,area(p,n));
    }
    return 0;
}
