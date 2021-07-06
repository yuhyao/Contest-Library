#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<queue>

int next[1100000],ans;
void getnext(char* T)
{
    next[0]=-1;
    int j=0,k=-1,l=strlen(T);
    while(j<l){
        if (k==-1||T[j]==T[k])
            next[++j]=++k;
        else k=next[k];
    }
}

void KMP(char* S,char* T)
{
    int i=0,j=0,l=strlen(S),lT=strlen(T);
    while (i<l)
    {
        if (j==-1 || S[i]==T[j])
        {
            ++i;++j;
            if (j==lT)
            {
                ++ans;
                j=next[j];
            }
        }
        else j=next[j];
    }
}

int t;
char S[1100000],T[1100000];


int main(){
    scanf("%d",&t);getchar();
    while (t--){
        ans=0;
        gets(T);getnext(T);
        gets(S);KMP(S,T);
        printf("%d\n",ans);
    }
    return 0;
}
