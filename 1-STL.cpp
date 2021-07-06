#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define maxn 1000
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

void VECTOR()
{
    vector<int> vec;
    int x,i;
    vec.push_back(x);//在数组末端加入x。
    vec.insert(vec.begin()+i,x);//在第i号元素前面插入x。
    vec.erase(vec.begin()+i);//删除第i号元素。
    x=vec.size();//将vec元素个数赋值给x。
    vec.clear();//清空vec。
}
void STACK()
{
    stack <int> s;
    int x;
    x=s.empty();//当栈空时返回true。
    s.push(x);//将x放到栈的顶端。
    x=s.top();//将栈顶元素赋值给x。
    s.pop();//弹出栈顶元素，并不会返回被弹出元素的值。
    x=s.size();//将栈元素个数赋值给x。
}
void QUEUE()
{
    queue <int> q;
    int x;
    q.push(x);//将x放到队列的末端。
    q.pop();//弹出队头元素，并不会返回被弹出元素的值。
    x=q.front();//将队头元素赋值给x。
    x=q.back();//将队头元素赋值给x。
    x=q.empty();//当队列空时返回true。
    x=q.size();//将队列元素个数赋值给x。
}
void SET()//multiset同样适用。
{
    set<int> s;
    set<int>::iterator it;//定义set的迭代器，对于multiset，应写multiset<int>::iterator it;
    int x=1;
    s.insert(x);//将x插入到集合中。
    it=s.begin();//返回指向第一个元素的迭代器。
    it=s.end();//返回指向最后一个元素之后的迭代器，不是最后一个元素。
    x=s.empty();//当集合空时返回true。
    s.erase(x);//将集合中所有值为x的元素删除。
    s.erase(it);//将集合中迭代器为it指向的元素删除。
    x=s.size();//将集合中元素的数目赋值给x。
    it=s.find(x);//返回一个指向x的迭代器，若集合中无x，则返回s1.end()。
    it=s.lower_bound(x);//返回集合中指向第一个大于等于x的元素的迭代器。
    it=s.upper_bound(x);//返回集合中指向第一个大于x的元素的迭代器。
    x=s.count(x);//返回集合中x的个数。
    s.clear();//清空集合。
}
void MAP()
{
    map<string,int> M;
    //std::tr1::unordered_map<long long,int> M;
    map<string,int>::iterator it;//定义map的迭代器。
    int x;
    string ss="haha";
    x=M.empty();//当map空时返回true。
    M["haha"]=x;//在map中修改"haha"对应的value为x，如果map中无"haha"，则新建一个。
    it=M.find(ss);//返回一个指向ss的迭代器，若集合中无ss，则返回M.end()。
    x=M.size();//将map中键值的数目赋值给x。
    x=M.count(ss);//返回map中ss的个数。
    M.erase(ss);//将map中所有键值为ss的元素删除。
    M.erase(it);//将map中迭代器为it指向的元素删除。
    M.clear();//清空map。
}
void PRIO()
{
    priority_queue <int> q;
    int x;
    x=q.empty();//当优先队列空时返回true。
    q.push(x);//在优先队列中插入x。
    x=q.top();//将优先队列队头元素赋值给x。
    q.pop();//弹出优先队列队头元素。
    x=q.size();//返回优先队列中元素的个数。
}
void BITSET()
{
    bitset<maxn> bit;
    int x=0;
    bit.set();//全部置1
    bit.reset();//全部置0
    bit.flip();//全部取反
    bit.set(x);//第x位置1
    bit.reset(x);//第x位置0
    bit.flip(x);//第x位取反
    x=bit.count();//返回bit中1的个数
    x=bit.any();//返回bit中是否有1
    x=bit.none();//返回bit中是否全0
    string s=bit.to_string();
    for(int j=bit._Find_first();j!=bit.size();j=bit._Find_next(j));
}
void PBDS()
{
    int i=0;
    tree<int,null_type,greater<int>,rb_tree_tag,tree_order_statistics_node_update> S; //The biggest value is in the first place.
    //if null_type does not work, then use null_mapped_type instead.
    
    S.insert(1); //insert integer 1.
    S.insert(2); //insert integer 2.
    printf("%d\n",(int)S.order_of_key(1)); //ask the number of elements in S which are greater than 1.
    printf("%d\n",*S.find_by_order(i)); //ask the i-th biggest element in S. i starts form 0.
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int myrand(int l,int r) {return l+rng()%(r-l+1);}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0);
    
    int size = 512 << 20; // 128MB
    char *p = (char*)malloc(size) + size;
    #if (defined _WIN64) or (defined __unix)
        __asm__("movq %0, %%rsp\n" :: "r"(p));
    #else
        __asm__("movl %0, %%esp\n" :: "r"(p));
    #endif
    
    exit(0);
}
