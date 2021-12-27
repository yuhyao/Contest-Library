template<class T,int LG> struct LB
{   // LG should not exceed the length of T in bits. Say LG can be at most 32 if you use T = u32.
    // last[i] = the last time the i-th basis shows appears in the sequence.
    T a[LG];
    int last[LG];
    T& operator [](const int &i) const {return (T&)a[i];}
    LB()
    {
        memset(a,0,sizeof a);
        memset(last,0,sizeof last);
    }
    void ins(T x,int ti=0)
    {
        per(i,0,LG-1) if(x>>i&1)
        {
            if(a[i]==0) {a[i]=x; last[i]=ti; return;}
            else if(ti>last[i]) swap(a[i],x), swap(last[i],ti);
            x^=a[i];
        }
    }
    friend LB operator +(const LB &a,const LB &b)
    {   // merging two bases.
        LB res = a;
        rep(i,0,LG-1) if(b[i]) res.ins(b[i]);
        return res;
    }
    T ask(T x,int ti=0)
    {   // ask what will we get if we eliminate $x$ using vectors appearing after time $ti$.
        per(i,0,LG-1) if(x>>i&1)
        {
            if(a[i]==0 || last[i]<ti) return x;
            x^=a[i];
        }
        return x;
    }
    T largest(int ti=0)
    {   // ask the largest value spanned by vectors appearing after time $ti$.
        T res = 0;
        per(i,0,LG-1) if((res>>i&1)==0 && a[i] && last[i]>=ti) res^=a[i];
        return res;
    }
    T kth(unsigned long long k,int ti = 0)
    {   // return the k-th smallest value spanned by vectors appearing after time $ti$. k starts from 0.
        int N=0;
        rep(i,0,LG-1) N+=(a[i]!=0 && last[i]>=ti);
        if((1ull<<N)<=k) return -1;
        T res=0;
        per(i,0,LG-1) if(a[i] && last[i]>=ti)
        {
            --N;
            int d = k>>N&1;
            if((int)(res>>i&1)!=d) res^=a[i];
        }
        return res;
    }
};

using u64 = unsigned long long;
using Base = LB<u64,32>;
Base intersect(Base A,const Base &B)
{   // Can only store numbers in [0,2^{32}-1]. Higher 32 bits are used to help the calculation.
    Base res;
    rep(i,0,31) if(A[i]) A[i]|=1ull<<(32+i);
    rep(i,0,31)
    {
        u64 x=A.ask(B[i]);
        if(x&((1ull<<32)-1)) A.ins(x);
        else
        {
            u64 y=0;
            rep(j,0,31) if((x>>(32+j))&1) y^=A[j];
            res.ins(y&((1ull<<32)-1));
        }
    }
    return res;   
}