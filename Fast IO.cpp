namespace fastIO {
    const int BUF_SIZE = 1 << 15;
    char buf[BUF_SIZE], *s = buf, *t = buf;
    inline int fetch() {
        if(s==t) {
            t=(s=buf)+fread(buf,1,BUF_SIZE,stdin);
            if(s==t) return EOF;
        }
        return *s++;
    }
    inline int read() {
        int a=0, b=1, c=fetch();
        while(!isdigit(c)) b^=(c=='-'), c=fetch();
        while(isdigit(c)) a=a*10+c-'0', c=fetch();
        return b?a:-a;
    }
}