typedef pii hashv;
const int MOD1=1000000007;
const int MOD2=998244353;

inline int Madd(int x,int y,int mod) {return x+y<mod?x+y:x+y-mod;}
inline int Msub(int x,int y,int mod) {return x-y>=0?x-y:x-y+mod;}

hashv operator +(const hashv &a,const hashv &b) {return {Madd(a.FI,b.FI,MOD1),Madd(a.SE,b.SE,MOD2)};}
hashv operator +(const hashv &a,const int &b) {return {Madd(a.FI,b,MOD1),Madd(a.SE,b,MOD2)};}
hashv operator -(const hashv &a,const hashv &b) {return {Msub(a.FI,b.FI,MOD1),Msub(a.SE,b.SE,MOD2)};}
hashv operator *(const hashv &a,const hashv &b) {return {1ll*a.FI*b.FI%MOD1,1ll*a.SE*b.SE%MOD2};}
hashv operator *(const hashv &a,const int &b) {return {1ll*a.FI*b%MOD1,1ll*a.SE*b%MOD2};}

const hashv base={131,10007}; //{100003,100019}
hashv pw[maxn+5];

struct hash_string
{
    // index starts from 1.
    hashv hx[maxn+5];
    void init(char* s)
    {
        int n=strlen(s+1);
        rep(i,1,n) hx[i]=hx[i-1]*base+s[i];
    }
    hashv get(int l,int r) {return hx[r]-hx[l-1]*pw[r-l+1];}
};
