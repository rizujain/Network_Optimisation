#include <stdlib.h>
#include "genRandGraph.h"

#define BOUND_BW 4096                         // to add weights in range [1,4096]
#define RAND_BOUND_BW (rand() % BOUND_BW + 1) // Add 1, weight may not be 0.
#define PERCENT 100

#ifdef SPARSE
void genSparseRandGraph(vector<vector<int>> &G, int n, int deg)
{
    vector<int> node(n, 0);
    for (int i = n - 1; i > 0; i--)
    {
        int j;
        while (node[i] < deg)
        {
            j = rand() % i;
            G[i][j] = RAND_BOUND_BW;
            G[j][i] = G[i][j];
            node[i]++;
            node[j]++;
        }
    }
}
#else
void genDenseRandGraph(vector<vector<int>> &G, int n, int prob)
{
    vector<int> node(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (((rand() % PERCENT) < prob) && (i != j))
            {
                G[i][j] = RAND_BOUND_BW;
                G[j][i] = G[i][j];
                node[i]++;
                node[j]++;
            }
        }
    }
}
#endif

void addWeightsEdges(vector<vector<int>> &G_2D, vector<vector<node>> &G_1D, int s, int t)
{
    int n = G_2D.size();
    int v1 = s;
    int vertex = 0;
    vector<vector<node>>::iterator l = G_1D.begin();

    for (int i = 0; i < n; ++i)
    {
        if ((i != s) && (i != t))
        {
            G_2D[v1][i] = RAND_BOUND_BW;
            G_2D[i][v1] = G_2D[v1][i]; // Add in both directions for undirected graphs
            v1 = i;
        }
    }
    G_2D[v1][t] = RAND_BOUND_BW;
    G_2D[t][v1] = G_2D[v1][t];

    for (vector<vector<int>>::iterator i = G_2D.begin(); i != G_2D.end(); i++)
    {
        for (vector<int>::iterator j = i->begin(); j != i->end(); j++)
        {

            if (*j != 0)
            {
                vertex = j - i->begin();
                node edge(vertex, *j);
                l->push_back(edge);
            }
        }
        l++;
    }
}