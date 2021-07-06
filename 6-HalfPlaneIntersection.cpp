#include<bits/stdc++.h>
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,a,n) for(int i=n;i>=a;i--)
#define pb push_back
#define maxn 100000
using namespace std;
typedef double db;

const db eps=1e-9;
const db pi=acos(-1.0);
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
    db norm2() {return x*x+y*y;}
};
typedef vector<P> vp;

db dot(P a,P b) {return a.x*b.x+a.y*b.y;}
db cross(P a,P b) {return a.x*b.y-a.y*b.x;}

struct L
{
    P a,b;
    db angle;
    void get_angle(){angle=atan2(b.y-a.y,b.x-a.x);}
    L(){}
    L(P x,P y):a(x),b(y){get_angle();}
};
//规定左侧为内侧（即逆时针）
bool onleft(L l,P p) {return cross(l.b-l.a,p-l.a)>eps;}
bool onright(L l,P p) {return cross(l.b-l.a,p-l.a)<-eps;}
//注意这个求交点没有考虑直线平行，要在外面考虑
P lcross(L l1,L l2)
{
    db s1=cross(l1.a-l2.a,l2.b-l2.a);
    db s2=cross(l1.b-l2.a,l2.b-l2.a);
    if(s1-s2==0) assert(0);
    return (l1.b*s1-l1.a*s2)/(s1-s2);
}

vp HPI(vector<L> l)
{
    int n=l.size();
    vector<L> q(n);
    sort(l.begin(),l.end(),[](L s1,L s2)
    {
        //先按极角排序，极角相等，内侧靠前
        if(cmp(s1.angle,s2.angle)!=0) return s1.angle<s2.angle;
        return onleft(s2,s1.b);
    });
    int tmp=1;
    rep(i,1,n-1) if(cmp(l[i].angle,l[tmp-1].angle)!=0) l[tmp++]=l[i];
    n=tmp;
    q[0]=l[0];q[1]=l[1];
    int front=0,rear=1;
    rep(i,2,n-1)
    {
        if(front<rear && sgn(cross(q[rear].b-q[rear].a,q[rear-1].b-q[rear-1].a))==0) return vp{};
        while(front<rear && onright(l[i],lcross(q[rear],q[rear-1]))) rear--;
        while(front<rear && onright(l[i],lcross(q[front],q[front+1]))) front++;
        q[++rear]=l[i];
    }
    if(front<rear && sgn(cross(q[rear].b-q[rear].a,q[rear-1].b-q[rear-1].a))==0) return vp{};
    while(front<rear && onright(q[front],lcross(q[rear],q[rear-1]))) rear--;
    while(front<rear && onright(q[rear],lcross(q[front],q[front+1]))) front++;
    if(front==rear) return vp{};
    vp res;
    rep(i,front,rear-1) res.pb(lcross(q[i],q[i+1]));
    if(rear-front>1) res.pb(lcross(q[front],q[rear]));
    return res;
}

int main()
{
    return 0;
}