template<class T> struct monoqueue
{
    pair<T,int> a[maxn+5];
    int head,rear;
    void init() {head=0; rear=-1;}

    monoqueue<T>(){init();}
    void push(T x,int id)
    {
        // interested in minimum value in the window.
        while(head<=rear && a[rear].FI>=x) rear--;
        a[++rear]={x,id};
    }
    // pop elements with index < id.
    void pop(int id) 
    {
        while(head<=rear && a[head].SE<id) head++;
    }
    bool empty() {return head>rear;}
    int size() {return rear-head+1;}
    T front() {assert(size()); return a[head].FI;}
};