#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

#include "genRandGraph.h"
#include "heapStruct.h"
#include "routing_algo.h"

bool G_NEW_ITERATION = false;
/* Infinite value is declared as the maximum value that int can hold*/
const int infinite_val = std::numeric_limits<int>::max();

/* status variables for vertices in Djikstra Algorithm */
const int IN_TREE = 2; // added in max bandwidth path
const int FRINGE = 1;  // neighbour detected
const int UNSEEN = 0;  // vertex not seen yet

/* Print path, function only gets called when PRINTPATH macro is defined */
void pathTraversal(vector<int> &dad, int t)
{
    if (dad[t] == -1)
    {
        printf("%d", t);
        return;
    }
    else
    {
        /* Recurse with the dad of the vertex */
        pathTraversal(dad, dad[t]);
    }
    printf(" -> %d", t);
    return;
}

/* Implementation of Djikstra withouth using Heap structure */
int djikstraNoHeap(vector<vector<node>> G, int s, int t)
{
    int n = G.size();
    // Initialise vertices set and parameters
    vector<int> status(n, UNSEEN), maxbw(n, 0), dad(n, -1);

    // maxbw[t] will contain the shortest path maximum bandwidth at the end of this function.
    maxbw[s] = infinite_val;
    status[s] = IN_TREE;

    /* for every vertex u in V */
    vector<node>::iterator i = G[s].begin();
    while (i != G[s].end())
    {
        int w = i->vertex;
        dad[w] = s;
        maxbw[w] = i->weight;
        status[w] = FRINGE;
        i++;
    }

    /* check every fringe, add the one with max bandwidth */
    while (status[t] != IN_TREE)
    {
        /* BUG:: Initialise here only. at the start of function > segmentation fault.*/
        int weight_MBP = -1;
        int vertex_MBP = -1;
        int i = 0;
        while (i < n)
        {
            if ((status[i] == FRINGE) && (weight_MBP < maxbw[i]))
            {
                vertex_MBP = i;
                weight_MBP = maxbw[i];
            }
            i++;
        }

        /* Add the vertex into the tree and update the status of the newly uncovered FRINGE vertices*/
        if (vertex_MBP != -1)
        {
            int v = vertex_MBP;
            status[v] = IN_TREE;

            auto i = G[v].begin();
            while (i != G[v].end())
            {
                int w = i->vertex;
                int wt = i->weight;
                if (status[w] == UNSEEN)
                {
                    status[w] = FRINGE;
                    dad[w] = v;
                    maxbw[w] = min(maxbw[v], wt); // update the max bandwidth value here
                }
                else if ((maxbw[w] < min(maxbw[v], wt)) && (status[w] == FRINGE))
                {
                    maxbw[w] = min(maxbw[v], wt);
                    dad[w] = v;
                }
                ++i;
            }
        }
        else
        {
            /* You will only reach here if there is no path*/
            return 0;
        }
    }
#ifdef PRINTPATH
    pathTraversal(dad, t);
    printf("\r\n");
#endif
    return maxbw[t];
}

/* Implementation of Djikstra using Heap structure */
int djikstraHeap(vector<vector<node>> G, int s, int t)
{
    int n = G.size();
    vector<int> status(n, UNSEEN), maxbw(n, 0), dad(n, -1);

    /* init max heap structure*/
    heap heapDjikstra(n);

    maxbw[s] = infinite_val;
    status[s] = IN_TREE;

    vector<node>::iterator i = G[s].begin();
    while (i != G[s].end())
    {
        int w = i->vertex;
        dad[w] = s;
        maxbw[w] = i->weight;
        status[w] = FRINGE;

        /*Insert a node in the heap*/
        heapDjikstra.insert(heapNode(w, maxbw[w]));

        i++;
    }

    while (status[t] != IN_TREE)
    {
        if (heapDjikstra.empty() == true)
            return 0;
        else
        {
            heapNode maxBWfringe = heapDjikstra.get_max();
            heapDjikstra.del(0);

            int v = maxBWfringe.vertex;
            status[v] = IN_TREE;
            auto i = G[v].begin();
            while (i != G[v].end())
            {
                int w = i->vertex;
                int wt = i->weight;
                if (status[w] == UNSEEN)
                {
                    dad[w] = v;
                    status[w] = FRINGE;
                    maxbw[w] = min(maxbw[v], wt);
                    heapDjikstra.insert(heapNode(w, maxbw[w]));
                }
                else if (status[w] == FRINGE)
                {
                    if (maxbw[w] < min(maxbw[v], wt))
                    {
                        int fringePos = heapDjikstra.get_idxVertex(w);
                        heapDjikstra.del(fringePos);
                        dad[w] = v;
                        maxbw[w] = min(maxbw[v], wt);
                        heapDjikstra.insert(heapNode(w, maxbw[w]));
                    }
                }
                i += 1;
            }
        }
    }
#ifdef PRINTPATH
    pathTraversal(dad, t);
    printf("\r\n");
#endif
    return maxbw[t];
}

void doDFS(const vector<vector<node>> &G, vector<node> &path, int s, int t)
{
    int n = G.size();
    enum color_group
    {
        white,
        gray,
        black
    };

    /* Init all vertices */
    static vector<color_group> status(n, white);
    static bool ifPath = false;

    if (G_NEW_ITERATION)
    {
        vector<color_group> status_new(n, white);
        status = status_new;
        ifPath = false;
        G_NEW_ITERATION = false;
    }

    if (s == t)
    {
        ifPath = true;
        return;
    }
    else // s!=t
    {
        status[s] = gray;
        auto i = G[s].begin();
        while (i != G[s].end())
        {
            if (status[i->vertex] == white)
            {
                path.push_back(*i);
                doDFS(G, path, i->vertex, t);
                if (ifPath == true)
                {
                    return;
                }
            }
            i += 1;
        }
        status[s] = black;
        if (!path.empty())
        {
            path.pop_back();
        }
    }
}

int Find(const vector<int> &D, int v)
{
    int w = 0;
    for (w = v; D[w] != -1;)
    {
        w = D[w];
    }
    return w;
}

void Union(int r1, int r2, vector<int> &D, vector<int> &rank)
{
    if (rank[r1] < rank[r2])
    {
        D[r1] = r2;
    }
    else if (rank[r2] < rank[r1])
    {

        D[r2] = r1;
    }
    else
    {
        rank[r1]++;
        D[r2] = r1;
    }
}

void MakeSet(vector<vector<node>> &G, priority_queue<edge> &heapEdges)
{
    int u = 0;
    auto i = G.begin();
    while (i != G.end())
    {
        auto j = i->begin();
        while (j != i->end())
        {
            int v = j->vertex;
            if (v > u)
            {
                heapEdges.push(edge(u, v, j->weight));
            }
            ++j;
        }
        u++;
        ++i;
    }
}

void heapSort(priority_queue<edge> &h, vector<edge> &edgeTosort)
{
    while (h.empty() == 0) // until all elements are sorted
    {
        const edge element = h.top();
        edgeTosort.push_back(element);
        h.pop(); // reduce heap size
    }
}

int kruskalHeap(vector<vector<node>> G, int s, int t)
{
    int n = G.size();
    int u = 0;
    priority_queue<edge> heapEdges;
    vector<edge> edgeTosort;

    vector<node> path;
    vector<vector<node>> G_spanTree(n);
    vector<int> D(n, -1), rank(n, 0);

    MakeSet(G, heapEdges);
    heapSort(heapEdges, edgeTosort);

    for (auto i = edgeTosort.begin(); i != edgeTosort.end(); ++i)
    {
        int r1, r2, v1, v2;
        v1 = i->u;
        v2 = i->v;

        r1 = Find(D, v1);
        r2 = Find(D, v2);
        node node1 = node(v2, i->wt);
        node node2 = node(v1, i->wt);
        if (r2 != r1)
        {
            G_spanTree[v1].push_back(node1);
            G_spanTree[v2].push_back(node2);
            Union(r1, r2, D, rank);
        }
    }

    doDFS(G_spanTree, path, s, t);
    if (!path.empty())
    {
        int maxbw = infinite_val;
        for (auto i = path.begin(); i != path.end(); ++i)
        {
            maxbw = min(maxbw, i->weight);
        }

#ifdef PRINTPATH
        printf("%d", s);
        for (auto i = path.begin(); i != path.end(); ++i)
        {
            printf(" -> %d", i->vertex);
        }
#endif
        printf("\r\n");
        return maxbw;
    }
    return 0;
}