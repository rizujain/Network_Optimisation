#include <vector>
using std::vector;

class node
{
public:
    int vertex;
    int weight;
    node(int v, int e) : vertex(v), weight(e) {}
};

class edge
{
public:
    int u;
    int v;
    int wt;
    edge(int v1, int v2, int bw) : u(v1), v(v2), wt(bw) {}

    //Operator Overloading
    friend bool operator>(const edge &a, const edge &b)
    {
        return (a.wt > b.wt);
    }
    friend bool operator<(const edge &a, const edge &b)
    {
        return (a.wt < b.wt);
    }
};

#ifdef SPARSE
void genSparseRandGraph(vector<vector<int>> &G, int n, int m);
#else
void genDenseRandGraph(vector<vector<int>> &G, int n, int p);
#endif
void addWeightsEdges(vector<vector<int>> &G, vector<vector<node>> &vectorG, int s, int t);