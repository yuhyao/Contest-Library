#include<cmath>
#include<cstdio>
#include<vector>
#include<algorithm>

const double pi=acos(-1.0);

const double eps=1e-8;
int cmp(double x){
    if (fabs(x)<eps) return 0;
    if (x>0) return 1;
        else return -1;
}

inline double sqr(double x){
    return x*x;
}

//MARK:点类 

struct point {
    double x,y;
    point(){}
    point (double a,double b): x(a), y(b) {}
    void input(){
        scanf("%lf%lf",&x,&y);
    }
    friend point operator + (const point &a,const point &b){
        return point(a.x+b.x,a.y+b.y);
    }
    friend point operator - (const point &a,const point &b){
        return point(a.x-b.x,a.y-b.y);
    }
    friend bool operator == (const point &a,const point &b){
        return cmp(a.x-b.x)==0 && cmp(a.y-b.y)==0;
    }
    
    friend point operator * (const double &a,const point &b){
        return point(a*b.x,a*b.y);
    }
    friend point operator / (const point &a,const double &b){
        return point(a.x/b,a.y/b);
    }
    double norm(){
        return sqrt(sqr(x)+sqr(y));
    }
};

//MARK:点运算

double det(const point &a,const point &b){
    return a.x*b.y-a.y*b.x;
} 
double dot(const point &a,const point &b){
    return a.x*b.x+a.y*b.y;
}
double dist(const point &a,const point &b){
    return (a-b).norm();
}
point rotate_p(const point &p,double A){
    double tx=p.x,ty=p.y;
    return point(tx*cos(A)-ty*sin(A),tx*sin(A)+ty*(cos(A)));
}


//MARK:点p到线段距离 
double dis_point_segment(point p,point s,point t){
    if (cmp(dot(p-s,t-s))<0) return (p-s).norm();
    if (cmp(dot(p-t,s-t))<0) return (p-t).norm();
    return fabs(det(s-p,t-p)/dist(s,t));
}
//MARK:点p到直线的垂足
point Pro(point p,point s,point t){
    double r=dot(t-s,p-s)/dot(t-s,t-s);
    return s+r*(t-s);
} 
bool On (point p,point s,point t){
    return cmp(det(p-s,t-s))==0 && cmp(dot(p-s,p-t))<=0;
}

bool parallel(point a,point b,point c,point d){
    return !cmp(det(a-b,c-d));
}

//MARK:直线相交
bool  cross(point a,point b,point c,point d,point &res){
    if (parallel(a,b,c,d)) return false;
    double s1=det(a-c,d-c);
    double s2=det(b-c,d-c);
    res=(s1*b-s2*a)/(s1-s2);
    return true;
}

//多边形类 

const int maxn=100;
struct polygon {
    int n;
    point a[maxn];
    polygon(){}
    //周长 
    double perimeter(){
        double sum=0;
        a[n]=a[0];
        for (int i=0;i<n;++i) sum+=(a[i+1]-a[i]).norm();
        return sum;
    }
    //面积
    double area(){
        double sum=0;
        a[n]=a[0];
        for (int i=0;i<n;++i) sum+=det(a[i+1],a[i]);
        return sum/2.;
    }
    //点在内部判断 
    int In(point t){
        int num=0,i,d1,d2,k;
        a[n]=a[0];
        for (int i=0;i<n;++i){
            if (On(t,a[i],a[i+1])) return 2;
            k=cmp(det(a[i+1]-a[i],t-a[i]));
            d1=cmp(a[i].y-t.y);
            d2=cmp(a[i+1].y-t.y);
            if (k>0 && d1<=0 && d2>0) ++num;
            if (k<0 && d2<=0 && d1>0) --num;
        }
        return num!=0;
    }
    point MaseCenter();
}; 
//MARK:重心 
point a[maxn];
point polygon::MaseCenter(){
    point ans=point(0,0);
    if (cmp(area()==0)) return ans;
    a[n]=a[0];
    for (int i=0;i<n;++i) ans=ans+det(a[i+1],a[i])*(a[i]+a[i+1]);
    return ans/area()/6.;
}

//MARK:凸包
struct polygon_convex {
    std::vector<point> P;
    polygon_convex(int size=0){
        P.resize(size);
    }
}; 

bool comp_less(const point &a,const point &b){
    return cmp(a.x-b.x)<0 || (cmp(a.x-b.x)==0 && cmp(a.y-b.y)<0);
}
//MARK:构造凸包 
polygon_convex convex_hull(std::vector<point> a){
    polygon_convex res(2*a.size()+5);
    sort(a.begin(),a.end(),comp_less);
    a.erase(unique(a.begin(),a.end()),a.end());
    int m=0;
    for (int i=0;i<a.size();++i){
        while (m>1 && cmp(det(res.P[m-1]-res.P[m-2],a[i]-res.P[m-2]))<=0) --m;
        res.P[m++]=a[i];
    }
    int k=m;
    for (int i=int(a.size())-2;i>=0;--i){
        while (m>k && cmp(det(res.P[m-1]-res.P[m-2],a[i]-res.P[m-2]))<=0) --m;
        res.P[m++]=a[i];
    }
    res.P.resize(m);
    if (a.size()>1) res.P.resize(m-1);
    return res;
}

//MARK:logn判断
int containIn(const polygon_convex &a,const point &b){
    int n=a.P.size();
    point g=(a.P[0]+a.P[n/3]+a.P[2*n/3])/3.0;
    int l=0,r=n;
    while (l+1<r) {
        int mid=(l+r)/2;
        if (cmp(det(a.P[l]-g,a.P[mid]-g))>0){
            if (cmp(det(a.P[l]-g,b-g))>=0 && cmp(det(a.P[mid]-g,b-g))<0) r=mid;
                else l=mid;
        }else {
            if (cmp(det(a.P[l]-g,b-g))<0 && cmp(det(a.P[mid]-g,b-g))>=0) l=mid;
                else r=mid;
        }
    }
    r%=n;
    int z=cmp(det(a.P[r]-b,a.P[l]-b))-1;
    if (z==-2) return 1;
    return z;
} 

double convex_diameter(polygon_convex &a,int &First,int &Second){
    std::vector<point> &p=a.P;
    int n=p.size();
    double maxd=0.0;
    if (n==1) {
        First=Second=0;
        return maxn;
    }
    #define next(i) ((i+1)%n)
    for (int i=0,j=1;i<n;++i) {
        while (cmp(det(p[next(i)]-p[i],p[j]-p[i])-det(p[next(i)]-p[i],p[next(j)]-p[i]))<0)
        {
            j=next(j);
        }
        double d=dist(p[i],p[j]);
        if (d>maxd){
            maxd=d;
            First=i,Second=j;
        }
        d=dist(p[next(i)],p[next(j)]);
        if (d>maxd){
            maxd=d;
            First=i,Second=j;
        }
    }
    return maxd;
}


