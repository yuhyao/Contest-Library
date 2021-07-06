#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define maxn 50000
using namespace std;
typedef double db;

const db eps=1e-8;
int sgn(db x) {return (x>eps)-(x<-eps);}
int cmp(db x,db y) {return sgn(x-y);}
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
    P unit() {return *this/norm();}
};
typedef vector<P> vp;

// when you use the following two functions, say to test if vectors are collinear,
// you should make sure that the coordinates are integers. Otherwise precision error
// might be enlarged by the norm.
db dot(P a,P b) {return a.x*b.x+a.y*b.y;}
db cross(P a,P b) {return a.x*b.y-a.y*b.x;}

db unitdot(P a,P b) {return dot(a.unit(),b.unit());}
db unitcross(P a,P b) {return cross(a.unit(),b.unit());}

bool ang_cmp(P a,P b) // used when x and y are integers.
{
    bool upa=a.y>0 || (a.y==0 && a.x<0);
    bool upb=b.y>0 || (b.y==0 && b.x<0);
    if(upa!=upb) return upa<upb;
    return cross(a,b)>0;
}

P rotate_point(P a,db sita)
{
    db x=a.x,y=a.y;
    return P(x*cos(sita)-y*sin(sita),x*sin(sita)+y*cos(sita));
}
struct L
{
    P a,b;
    L(){}
    L(P x,P y):a(x),b(y){}
};
//点p到线段st距离
db dis_p_seg(P p,P s,P t)
{
    if(sgn(dot(p-s,t-s))<0) return (p-s).norm();
    if(sgn(dot(p-t,s-t))<0) return (p-t).norm();
    return fabs(cross(s-p,t-p)/(s-t).norm());
}
//点p到直线st垂足
P p_proj_l(P p,P s,P t)
{
    db r=dot(p-s,t-s)/dot(t-s,t-s);
    return s+(t-s)*r;
}
//点p在线段st上(包括端点)
bool p_on_seg(P p,P s,P t)
{
    return sgn(unitcross(p-s,t-s))==0 && sgn(unitdot(p-s,p-t))<=0;
}
//点p在直线st上
bool p_on_line(P p,P s,P t)
{
    return sgn(unitcross(p-s,t-s))==0;
}
//判断直线l1,l2是否相交，相交返回交点
bool l_cross(L l1,L l2,P &a)
{
    if(!sgn(cross(l1.a-l1.b,l2.a-l2.b))) return 0;
    db s1=cross(l1.a-l2.a,l2.b-l2.a);
    db s2=cross(l1.b-l2.a,l2.b-l2.a);
    a=(l1.b*s1-l1.a*s2)/(s1-s2);
    return 1;
}
//求线段ab是否与cd相交。1为规范相交，0为不相交，-1为非规范相交。
int ab_cross_cd(P a,P b,P c,P d)
{
    int d1,d2,d3,d4;
    d1=sgn(unitcross(b-a,c-a));
    d2=sgn(unitcross(b-a,d-a));
    d3=sgn(unitcross(d-c,a-c));
    d4=sgn(unitcross(d-c,b-c));
    if((d1^d2)==-2 && (d3^d4)==-2) return 1;
    if(d1==0 && p_on_seg(c,a,b)) return -1;
    if(d2==0 && p_on_seg(d,a,b)) return -1;
    if(d3==0 && p_on_seg(a,c,d)) return -1;
    if(d4==0 && p_on_seg(b,c,d)) return -1;
    return 0;
}
db area(vp a)
{
    if(a.size()==0) return 0;
    P a0=a[0];
    for(auto &p: a) p=p-a0;
    int n=a.size();
    db sum=0;
    rep(i,0,n-1) sum+=cross(a[i],a[(i+1)%n]);
    return sum/2;
}
P center(vp a)
{
    db S=area(a);
    if(sgn(S)==0) return P(0,0);
    P a0=a[0];
    for(auto &p: a) p=p-a0;
    int n=a.size();
    P ans(0,0);
    rep(i,0,n-1) ans=ans+(a[i]+a[(i+1)%n])*(cross(a[i],a[(i+1)%n])/(S*6));
    return ans+a0;
}
// always check if we should use cross or unitcross for judging collinearity.
vp Graham(vp a)
{
    int n=a.size(),k=0;
    rep(i,0,n-1) if(a[i].y<a[k].y || (a[i].y==a[k].y && a[i].x<a[k].x)) k=i;
    swap(a[0],a[k]);
    sort(a.begin()+1,a.end(),[a0=a[0]](P s,P t) {
        db z=cross(s-a0,t-a0);
        if(sgn(z)==1 || (sgn(z)==0 && cmp((s-a0).norm(),(t-a0).norm())<0)) return 1;
        return 0;
    });
    vp p(n);
    int top=1;
    p[0]=a[0];
    p[1]=a[1];
    rep(i,2,n-1)
    {
        while(top && sgn(cross(p[top]-p[top-1],a[i]-p[top-1]))<=0) top--;
        p[++top]=a[i];
    }
    p.resize(top+1);
    return p;
}
db rotating_calipers(int n,P p[])
{
    db ans=0;
    p[n]=p[0];
    int ptr=1;
    rep(i,0,n-1)
    {
        while(cross(p[i+1]-p[i],p[ptr+1]-p[i])>cross(p[i+1]-p[i],p[ptr]-p[i])) ptr=(ptr+1)%n;
        ans=max(ans,max((p[ptr]-p[i]).norm(),(p[ptr]-p[i+1]).norm()));
    }
    return ans;
}

int main()
{
    return 0;
}
