#include<cstdio>
#include<string>
#define ll long long;
using namespace std;

const int oo=1<<25;
const int al=53; //大写字母注意处理，可以把其处理成其小写字母+26； 
const int maxn=210000; //少年，卡内存无疑 

int root,last_added,pos,needsl,remainder,ac_node,ac_e,ac_len;

struct node{
    int start,end,slink;
    int next[al];
    int edge_length(){
        return min(end+1,pos+1)-start;
    }
};

node tree[2*maxn]; //最坏情况节点数=字符串长度*2； 
char text[maxn];

int new_node(int start,int end=oo){
    node nd;
    nd.start=start;
    nd.end=end;
    nd.slink=0;
    for (int i=0;i<al;++i)
        nd.next[i]=0;
    tree[++last_added]=nd;
    return last_added;
}

inline char ac_edge(){
    return text[ac_e]-'a';
}

void add_sl(int node){
    if (needsl>0) tree[needsl].slink=node;
    needsl=node;
}

bool walk_down(int node){
    int x=tree[node].edge_length();
    if (ac_len>=x){
        ac_e+=x;
        ac_len-=x;
        ac_node=node;
        return true;
    }
    return false;
}

void st_init(){
    needsl=0,last_added=0,pos=-1,
    remainder=0,ac_node=1,ac_e=0,ac_len=0;
    root=ac_node=new_node(-1,-1);
}

void st_extend(char c){
    text[++pos]=c;
    needsl=0;
    remainder++;
    while(remainder>0){
        if (ac_len==0) ac_e=pos;
        if (tree[ac_node].next[ac_edge()]==0){
            int leaf=new_node(pos);
            tree[ac_node].next[ac_edge()]=leaf;
            add_sl(ac_node); 
    } else {
        int nxt=tree[ac_node].next[ac_edge()];
        if (walk_down(nxt)) continue;
        if (text[tree[nxt].start+ac_len]==c){
            ac_len++;
            add_sl(ac_node); //若该阶段已存在中间节点，则该点一定为中间节点
            break; 
        }
        int split=new_node(tree[nxt].start,tree[nxt].start+ac_len-1);
        tree[ac_node].next[ac_edge()]=split;
        int leaf=new_node(pos);
        tree[split].next[c-'a']=leaf;
        tree[nxt].start+=ac_len;
        tree[split].next[text[tree[nxt].start-'a']]=nxt;
        add_sl(split);
    }
    --remainder;
        if (ac_node==root && ac_len>0){
            --ac_len;
            ac_e=pos-remainder+1;
        } else
            ac_node=tree[ac_node].slink>0?tree[ac_node].slink:root;
    }
}

int main(){
    return 0;
}

