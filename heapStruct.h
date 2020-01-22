#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include <vector>
using std::vector;

class heapNode
{
public:
    int vertex;
    int bandwidth;
    heapNode(int v, int bw) : vertex(v), bandwidth(bw) {}

    //Operator Overloading
    friend bool operator>(const heapNode &a, const heapNode &b)
    {
        return (a.bandwidth > b.bandwidth);
    }
    friend bool operator<(const heapNode &a, const heapNode &b)
    {
        return (a.bandwidth < b.bandwidth);
    }
};

class heap
{
private:
    vector<heapNode> H;
    vector<int> idx_vertex;
    void swap(int i, int j);
    void fixHeap_movUP(int i);
    void fixHeap_movDOWN(int i);

public:
    heap(int n) : idx_vertex(n, -1) {}
    heapNode get_max();
    bool empty();
    int get_idxVertex(int vertex);
    void insert(heapNode a);
    void del(int h);
};
#endif
