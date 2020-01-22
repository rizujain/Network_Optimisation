#ifndef MAXBW_H_INCLUDED
#define MAXBW_H_INCLUDED

#include <vector>
using std::vector;

void printPath(vector<int> &prev, int t);
int djikstraNoHeap(vector<vector<node>> G, int s, int t);
int djikstraHeap(vector<vector<node>> G, int s, int t);
int kruskalHeap(vector<vector<node>> G, int s, int t);

extern bool G_NEW_ITERATION;

#endif
