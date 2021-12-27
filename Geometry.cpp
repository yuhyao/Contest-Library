const db pi = acos(-1.0);
const db eps = 1e-9;
int sgn(db x) {return (x>eps)-(x<-eps);}
int cmp(db x,db y) {return sgn(x-y);}
db sqr(db x) {return x*x;}

struct P
{
    db x,y;
    P():x(0),y(0){}
    P(db a,db b):x(a),y(b){}
    void in() {scanf("%lf%lf",&x,&y);}
    void out() {printf("%.10f %.10f\n",x,y);}
    P operator +(const P &a) const {return P(x+a.x,y+a.y);}
    P operator -(const P &a) const {return P(x-a.x,y-a.y);}
    P operator *(const db &a) const {return P(x*a,y*a);}
    P operator /(const db &a) const {return P(x/a,y/a);}
    bool operator == (const P &a) const {return cmp(x,a.x)==0 && cmp(y,a.y)==0;}
    bool operator < (const P &a) const {return cmp(x,a.x)==0?cmp(y,a.y)<0:x<a.x;}
    db len() const {return sqrt(x*x+y*y);}
    db len2() const {return x*x+y*y;}
    P unit() const {return *this/len();}

    db dot(const P &b) const {return x*b.x+y*b.y;}
    db cross(const P &b) const {return x*b.y-y*b.x;}
    // when you use the following two functions, say to test if vectors are collinear, you should make sure that the coordinates are integers. Otherwise precision error might be enlarged by the norm.

    db unitdot(const P &b) const {return unit().dot(b.unit());}
    db unitcross(const P &b) const {return unit().cross(b.unit());}
};
typedef vector<P> vp;

bool ang_cmp(P a,P b) // used when x and y are integers.
{
    bool upa=a.y>0 || (a.y==0 && a.x<0);
    bool upb=b.y>0 || (b.y==0 && b.x<0);
    if(upa!=upb) return upa<upb;
    return a.cross(b)>0;
}

P rotate_point(P a,db theta)
{
    db x=a.x,y=a.y;
    return P(x*cos(theta)-y*sin(theta),x*sin(theta)+y*cos(theta));
}
struct L
{
    P a,b; 
    db angle;
    void get_angle() {angle = atan2(b.y-a.y,b.x-a.x);}
    L(){}
    L(P x,P y):a(x),b(y){get_angle();}
};
// distance from point p to segment st.
db dis_p_seg(P p,P s,P t)
{
    if(sgn((p-s).dot(t-s))<0) return (p-s).len();
    if(sgn((p-t).dot(s-t))<0) return (p-t).len();
    return fabs((s-p).cross(t-p)/(s-t).len());
}
//projection of point p to line st.
P p_proj_l(P p,P s,P t)
{
    db r=(p-s).dot(t-s)/(t-s).dot(t-s);
    return s+(t-s)*r;
}
// check if point p is on seg st (including endpoints s and t.)
bool p_on_seg(P p,P s,P t)
{
    return sgn((p-s).unitcross(t-s))==0 && sgn((p-s).unitdot(p-t))<=0;
}
// check if point p is on line st.
bool p_on_line(P p,P s,P t)
{
    return sgn((p-s).unitcross(t-s))==0;
}
// check if line l1 intersects line l2. If yes, return it using para &a.
bool l_cross(L l1,L l2,P &a)
{
    if(sgn((l1.a-l1.b).unitcross(l2.a-l2.b))==0) return 0;
    db s1=(l1.a-l2.a).cross(l2.b-l2.a);
    db s2=(l1.b-l2.a).cross(l2.b-l2.a);
    a=(l1.b*s1-l1.a*s2)/(s1-s2);
    return 1;
}
// check if segment ab intersects segment cd: 
// 1 -> intersects and the cross is in the interior;
// 0 -> does not intersect;
// -1 -> intersects at the endpoint (a or b or c or d).
int ab_cross_cd(P a,P b,P c,P d)
{
    int d1,d2,d3,d4;
    d1=sgn((b-a).unitcross(c-a));
    d2=sgn((b-a).unitcross(d-a));
    d3=sgn((d-c).unitcross(a-c));
    d4=sgn((d-c).unitcross(b-c));
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
    rep(i,0,n-1) sum+=a[i].cross(a[(i+1)%n]);
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
    rep(i,0,n-1) ans=ans+(a[i]+a[(i+1)%n])*(a[i].cross(a[(i+1)%n])/(S*6));
    return ans+a0;
}
// always check if we should use cross or unitcross for judging collinearity.
vp Graham(vp a)
{
    int n=a.size(),k=0;
    rep(i,0,n-1) if(a[i].y<a[k].y || (a[i].y==a[k].y && a[i].x<a[k].x)) k=i;
    swap(a[0],a[k]);
    sort(a.begin()+1,a.end(),[a0=a[0]](P s,P t) {
        db z=(s-a0).cross(t-a0); // pay attention here.
        if(sgn(z)==1 || (sgn(z)==0 && cmp((s-a0).len(),(t-a0).len())<0)) return 1;
        return 0;
    });
    vp p(n);
    int top=1;
    p[0]=a[0];
    p[1]=a[1];
    rep(i,2,n-1)
    {
        while(top && sgn((p[top]-p[top-1]).cross(a[i]-p[top-1]))<=0) top--;
        p[++top]=a[i];
    }
    p.resize(top+1);
    return p;
}

// find indices of two tangent points from point p to convex hull A,
// return pair (l,r) where p can see A[l]-A[l+1]-...-A[r].
template<typename F> int CT_helper_bs(int n,F onright)
{
    int up=onright(0,1);
    int l=0,r=n;
    while(l<r)
    {
        int mid=(l+r)>>1;
        if(onright(0,mid))
        {
            if(up) l=mid+1;
            else r=mid;
        }
        else
        {
            if(onright(mid,(mid+1)%n)) r=mid;
            else l=mid+1;
        }
    }
    return l;
}
pii convex_tangent(vp &A, P p) 
{
    int n=A.szie();
    int l=bs(n,[&](int i,int j) {return (p-A[i]).cross(A[j]-A[i])>0;})%n;
    int r=bs(n,[&](int i,int j) {return (p-A[i]).cross(A[j]-A[i])<0;})%n;
    return {l,r};
}

db rotating_calipers(int n,P p[]) // find the longest diagonal in linear time.
{
    db ans=0;
    p[n]=p[0];
    int ptr=1;
    rep(i,0,n-1)
    {
        while((p[i+1]-p[i]).cross(p[ptr+1]-p[i]) > (p[i+1]-p[i]).cross(p[ptr]-p[i])) ptr = (ptr+1)%n;
        chmax(ans,(p[ptr]-p[i]).len());
        chmax(ans,(p[ptr]-p[i+1]).len());
    }
    return ans;
}

// Half plane intersection.
// Note that the resulting convex hull might have colinear points.
vp HPI(vector<L> l)
{
    // LHS <-> inside (i.e. counter clockwise)
    auto onleft = [](L l,P p) {return (l.b-l.a).cross(p-l.a)>eps;};
    auto onright = [](L l,P p) {return (l.b-l.a).cross(p-l.a)<-eps;};
    
    int n=l.size();
    vector<L> q(n);
    sort(l.begin(),l.end(),[&](L s1,L s2) {
        // sort according to the angle.
        if(cmp(s1.angle,s2.angle)!=0) return s1.angle<s2.angle;
        return onleft(s2,s1.b);
    });
    int tmp=1;
    rep(i,1,n-1) if(cmp(l[i].angle,l[tmp-1].angle)!=0) l[tmp++]=l[i];
    n=tmp;
    q[0]=l[0];q[1]=l[1];

    // Note that we assume l1 and l2 are not parallel.
    auto lcross = [](L l1,L l2) {
        db s1=(l1.a-l2.a).cross(l2.b-l2.a);
        db s2=(l1.b-l2.a).cross(l2.b-l2.a);
        if(s1-s2==0) assert(0);
        return (l1.b*s1-l1.a*s2)/(s1-s2);
    };

    int front=0,rear=1;
    rep(i,2,n-1)
    {
        if(front<rear && sgn((q[rear].b-q[rear].a).cross(q[rear-1].b-q[rear-1].a))==0) return vp{};
        while(front<rear && onright(l[i],lcross(q[rear],q[rear-1]))) rear--;
        while(front<rear && onright(l[i],lcross(q[front],q[front+1]))) front++;
        q[++rear]=l[i];
    }
    if(front<rear && sgn((q[rear].b-q[rear].a).cross(q[rear-1].b-q[rear-1].a))==0) return vp{};
    while(front<rear && onright(q[front],lcross(q[rear],q[rear-1]))) rear--;
    while(front<rear && onright(q[rear],lcross(q[front],q[front+1]))) front++;
    if(front==rear) return vp{};
    vp res;
    rep(i,front,rear-1) res.pb(lcross(q[i],q[i+1]));
    if(rear-front>1) res.pb(lcross(q[front],q[rear]));
    return res;
}

// Circle:
inline db mysqrt(db x) {return sqrt(max(0.0,x));}
// return the intersecting points of segment ab and circle C((0,0), r).
vp seg_inter_cir(P a,P b,P o,db r)
{
    vp res{};
    db x0=o.x,y0=o.y;
    db x1=a.x,y1=a.y;
    db x2=b.x,y2=b.y;
    db dx=x2-x1,dy=y2-y1;
    db A=sqr(dx)+sqr(dy);
    db B=2*dx*(x1-x0)+2*dy*(y1-y0);
    db C=sqr(x1-x0)+sqr(y1-y0)-sqr(r);
    db delta=B*B-4*A*C;
    if(sgn(delta)>0)
    {
        db t1=(-B-mysqrt(delta))/(2*A);
        db t2=(-B+mysqrt(delta))/(2*A);
        if(sgn(t1-1)<=0 && sgn(t1)>=0) res.pb(P(x1+t1*dx,y1+t1*dy));
        if(sgn(t2-1)<=0 && sgn(t2)>=0) res.pb(P(x1+t2*dx,y1+t2*dy));
    }
    return res;
}

db tri_inter_cir_area(P a,P b,db r)
{
    int ina=sgn(a.len()-r)<0;
    int inb=sgn(b.len()-r)<0;

    // Given points a and b on circle C((0,0), r), output the area of the sector.
    auto sector_area = [&](P &a,P &b) {
        db theta=atan2(a.y,a.x)-atan2(b.y,b.x);
        while(theta<=0) theta+=2*pi;
        while(theta>2*pi) theta-=2*pi;
        theta=min(theta,2*pi-theta);
        return r*r*theta/2;
    };

    if(ina)
    {
        if(inb) return fabs(a.cross(b))/2.0;
        else
        {
            vp p=seg_inter_cir(a,b,P(0,0),r);
            return sector_area(b,p[0])+fabs(a.cross(p[0]))/2.0;
        }
    }
    else
    {
        vp p=seg_inter_cir(a,b,P(0,0),r);
        if(inb) return sector_area(p[0],a)+fabs(p[0].cross(b))/2.0;
        else
        {
            if(p.size()==2) return sector_area(a,p[0]) + sector_area(p[1],b) + fabs(p[0].cross(p[1]))/2.0;
            else return sector_area(a,b);
        }
    }
}
// calculate the area of intersection of A and C((0,0), r).
db polygon_inter_cir_area(vp A,db r)
{
    int n=A.size();
    db ret=0;
    rep(i,0,n-1)
    {
        int SGN = sgn(A[i].cross(A[(i+1)%n]));
        ret += SGN * tri_inter_cir_area(A[i], A[(i+1)%n], r);
    }
    return fabs(ret);
}