#include<cstdio>
#include<string>
#include<vector>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

const int oo=1<<25;
const int maxn=200200; 


int root,last_added,pos,needsl,remainder,ac_node,ac_e,ac_len;

struct edd{
    char c;int to;
};

struct node{
    int start,end,slink;
    vector <edd> ed;
    int edge_length(){
        return min(end+1,pos+1)-start;
    }
    int next(char s){
        for (int i=0;i<ed.size();++i) if (ed[i].c==s) return ed[i].to;
        return 0;
    }
    int find(char s){
        for (int i=0;i<ed.size();++i) if (ed[i].c==s) return i;
    }    
};

node tree[2*maxn]; //最坏情况节点数=字符串长度*2； 
string text;

int new_node(int start,int end=oo){
    node nd;
    nd.start=start;
    nd.end=end;
    nd.slink=0;
    nd.ed.clear();
    tree[++last_added]=nd;
    return last_added;
}

inline char ac_edge(){
    return text[ac_e];
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
    remainder=0,ac_e=0,ac_len=0;
    root=ac_node=new_node(-1,-2);
    text="";
}

void st_extend(char c){
    int fd;
    text+=c;++pos;edd tmp;
    needsl=0;
    remainder++;
    while(remainder>0){
        if (ac_len==0) ac_e=pos;
        if (tree[ac_node].next(ac_edge())==0){
            int leaf=new_node(pos);
            tmp.c=ac_edge();tmp.to=leaf;
            tree[ac_node].ed.push_back(tmp);
            add_sl(ac_node); 
    } else {
        int nxt=tree[ac_node].next(ac_edge());
        if (walk_down(nxt)) continue;
        if (text[tree[nxt].start+ac_len]==c){
            ac_len++;
            add_sl(ac_node); //若该阶段已存在中间节点，则该点一定为中间节点
            break; 
        }
        int split=new_node(tree[nxt].start,tree[nxt].start+ac_len-1);
        fd=tree[ac_node].find(ac_edge());
        tree[ac_node].ed[fd].c=ac_edge();tree[ac_node].ed[fd].to=split;
        int leaf=new_node(pos);
        tmp.c=c;tmp.to=leaf;
        tree[split].ed.push_back(tmp);
        tree[nxt].start+=ac_len;
        tmp.c=text[tree[nxt].start];tmp.to=nxt;
        tree[split].ed.push_back(tmp);
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
