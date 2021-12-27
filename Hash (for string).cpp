using hashv = pair<int,int>;
const int mod1 = 1000000007;
const int mod2 = 1000050131;

inline int Madd(int x,int y,int mod) {return x+y<mod?x+y:x+y-mod;}
inline int Msub(int x,int y,int mod) {return x-y>=0?x-y:x-y+mod;}

hashv operator +(const hashv &a,const hashv &b) {return {Madd(a.FI,b.FI,mod1), Madd(a.SE,b.SE,mod2)};}
hashv operator +(const hashv &a,const int &b) {return {Madd(a.FI,b,mod1), Madd(a.SE,b,mod2)};}
hashv operator -(const hashv &a,const hashv &b) {return {Msub(a.FI,b.FI,mod1), Msub(a.SE,b.SE,mod2)};}
hashv operator *(const hashv &a,const hashv &b) {return {1ll*a.FI*b.FI%mod1, 1ll*a.SE*b.SE%mod2};}
hashv operator *(const hashv &a,const int &b) {return {1ll*a.FI*b%mod1, 1ll*a.SE*b%mod2};}

const hashv base={131,10007}; //{100003,100019}, {500009,500029}
hashv pw[maxn+5];

// indices start from 1.
void cal(char* s,vector<hashv> &hx)
{
    int n=strlen(s+1);
    hx.resize(n+1); 
    rep(i,1,n) hx[i]=hx[i-1]*base+s[i];
}
hashv get_hash(vector<hashv> &hx,int l,int r) {return hx[r]-hx[l-1]*pw[r-l+1];}