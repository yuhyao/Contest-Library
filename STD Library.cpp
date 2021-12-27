#include<ext/pb_ds/assoc_container.hpp> // always
#include<ext/pb_ds/tree_policy.hpp> // for trees
#include<ext/pb_ds/hash_policy.hpp> // for hash table
#include<ext/pb_ds/priority_queue.hpp> // for merging priority queue
using namespace __gnu_pbds;

void BITSET() {
    bitset<maxn> bit;
    x=bit.count(); // return the number of bit 1.
    x=bit.any(); // return if there is at least one bit 1.
    x=bit.none(); // return if there are all bit 0.
    string s=bit.to_string();
    for(int j=bit._Find_first();j!=sz(bit);j=bit._Find_next(j));
}
void PBDS() {
    // rank tree:
    tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update> S; //The biggest value is in the first place.
    // if null_type does not work, then use null_mapped_type instead.
    
    S.insert(1); //insert integer 1.
    printf("%d\n",(int)S.order_of_key(1)); // ask the number of elements in S which are greater than 1.
    printf("%d\n",*S.find_by_order(i)); // ask the i-th biggest element in S. i starts form 0.

    // hash table
    gp_hash_table<int,int> HT;

    __gnu_pbds::priority_queue<int, less<int>, binomial_heap_tag> p,q;
    p.join(q); // after doing this, q will be empty.
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int myrand(int l,int r) {return l+rng()%(r-l+1);}