#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

const int Maxn=1000000+100;
char str[Maxn];
int ans;
struct Aho_Corasick
{
    const static int maxnode=1000100;
    const static int type=26;
    int next[maxnode][type],fail[maxnode],end[maxnode],l[maxnode];
    int root,L;
    int newnode()
    {
        for (int i=0;i<type;++i)
            next[L][i]=-1;
            l[L]=0;            //height 
            end[L++]=0;
            return L-1;
    }
    void init()
    {
        L=0;
        root=newnode();
    }
    void insert(char* str)
    {
        int len=strlen(str);
        int now=root;
        for (int i=0;i<len;++i)
        {
            int id=str[i]-'a';
            if (next[now][id]==-1)
                next[now][id]=newnode();
            now=next[now][id];
        }
        ++end[now];
        l[now]=len;
    }
    void build()
    { 
        queue<int>Q;
        fail[root]=root;
        for (int i=0;i<type;++i)
            if(next[root][i]==-1)
                next[root][i]=root;
            else
            {
                fail[next[root][i]]=root;
                Q.push(next[root][i]);
            }
        while(!Q.empty())
        {
            int now=Q.front();
            Q.pop();
            for (int i=0;i<type;++i)
                if (next[now][i]==-1)
                    next[now][i]=next[fail[now]][i];
                else
                {
                    fail[next[now][i]]=next[fail[now]][i];
                    Q.push(next[now][i]);
                }
        }
    }
    void work(char* str)
    {
        int id;
        int len=strlen(str);
        int now=root;
        for (int i=0;i<len;++i)
        {
            //MARK:lowercase
            id=str[i]-'a';
            now=next[now][id];
            int temp=now;
            while(temp!=root)
            {
                if (end[temp]!=0)
                {
                    //MARK:action
                    ans+=end[temp];
                    end[temp]=0;
                }
                temp=fail[temp];
            }
        }
    }
}AC;

int t,n,tot;
char x;

int main()
{
    scanf("%d",&t);
    while(t--)
    {
        ans=0;
        AC.init();
        scanf("%d",&n);getchar();
        for (int i=1;i<=n;i++)
        {
            gets(str);
            AC.insert(str);
        }
        AC.build();
        gets(str);
        AC.work(str);
        printf("%d\n",ans);
    }
    return 0;
}
