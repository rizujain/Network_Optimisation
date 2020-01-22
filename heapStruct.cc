#include <iostream>
#include <assert.h>
using namespace std;

#include "heapStruct.h"

void heap::swap(int x, int y)
{
    int a = H[x].vertex;
    int b = H[y].vertex;
    idx_vertex[a] = y;
    idx_vertex[b] = x;
    heapNode temp = H[x];
    H[x] = H[y];
    H[y] = temp;
}

heapNode heap::get_max()
{
    return H.front();
}

void heap::fixHeap_movUP(int x)
{
    while ((x > 0) && (H[x] > H[(x - 1) / 2]))
    {
        swap((x - 1) / 2, x);
        x = (x - 1) / 2;
    }
}

int heap::get_idxVertex(int vertex)
{
    return idx_vertex[vertex];
}

void heap::insert(heapNode v)
{
    H.push_back(v);
    int newSize = H.size() - 1;
    idx_vertex[v.vertex] = newSize;
    fixHeap_movUP(newSize);
}

void heap::fixHeap_movDOWN(int x)
{
    int l, r;
    int largest = x;
    int len = H.size();

    l = 2 * x + 1;
    if (l < len)
    {
        if (H[l] > H[largest])
        {
            largest = l;
        }
    }

    r = 2 * (1 + x);
    if (r < len)
    {
        if (H[r] > H[largest])
        {
            largest = r;
        }
    }

    if (largest != x)
    {
        swap(x, largest);
        fixHeap_movDOWN(largest);
    }
}

void heap::del(int idx)
{
    int len = H.size();
    int node = H[idx].vertex;
    idx_vertex[node] = -1;

    if ((idx >= len) || (idx < 0))
    {
        printf("Err! Index %d Out of Bounds \r\n", idx);
        assert(false);
    }

    H[idx] = H.back();
    idx_vertex[(H.back()).vertex] = idx;
    H.pop_back();
    fixHeap_movDOWN(idx);
}

bool heap::empty()
{
    return (H.size() == 0);
}