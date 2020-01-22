// "=================================================="
// "This is an application programmed towards the Course Project"
// "CSCE 629 Analysis of Algorithms"
// "Author: Rizu Jain"
// "UIN: 430000753"
// "=================================================="

#include <iostream>
#include <ctime>
using namespace std;

/* Include header files */
#include "genRandGraph.h"
#include "routing_algo.h"

/* test with 5 s.t pairs on same graph generated*/
#define NUM_ITERATIONS 5

void test_djikstra_NonHeap(vector<vector<node>> G, int s, int t)
{
    clock_t start = 0;  // start point of running time
    double timeElapsed; // hold total time elapsed
    int bw = 0;         // resultant bandwidth
    start = clock();
    bw = djikstraNoHeap(G, s, t);
    timeElapsed = (clock() - start) / (double)CLOCKS_PER_SEC;
    printf("*** Time Elapsed = %lf \r\n", timeElapsed);
    printf("*** Max Bandwidth  = %d \r\n", bw);
}

void test_djikstra_Heap(vector<vector<node>> G, int s, int t)
{
    clock_t start = 0;  // start point of running time
    double timeElapsed; // hold total time elapsed
    int bw = 0;         // resultant bandwidth
    start = clock();
    bw = djikstraHeap(G, s, t);
    timeElapsed = (clock() - start) / (double)CLOCKS_PER_SEC;
    printf("*** Time Elapsed = %lf \r\n", timeElapsed);
    printf("*** Max Bandwidth  = %d \r\n", bw);
}

void test_kruskal_Heap(vector<vector<node>> G, int s, int t)
{
    clock_t start = 0;  // start point of running time
    double timeElapsed; // hold total time elapsed
    int bw = 0;         // resultant bandwidth
    start = clock();
    G_NEW_ITERATION = true;
    bw = kruskalHeap(G, s, t);
    timeElapsed = (clock() - start) / (double)CLOCKS_PER_SEC;
    printf("*** Time Elapsed = %lf \r\n", timeElapsed);
    printf("*** Max Bandwidth  = %d \r\n", bw);
}

/* Main Driver */
int main()
{
    int s;                 // source vertex
    int t;                 // destination vertex
    int n = 5000;          // Number of vertices
    int test_cases_st = 1; // test case of an s,t pair

#ifdef SPARSE
    int degree = 6; // average vertex degree for sparse graphs
    vector<vector<int>> G1_2D(n, vector<int>(n, 0));
    vector<vector<node>> G1(n);
#else
    int prob = 20; // percent probability of adjacent vertices in dense graphs
    vector<vector<int>> G2_2D(n, vector<int>(n, 0));
    vector<vector<node>> G2(n);
#endif

    printf("Hello World! Built on %s :: %s", __DATE__, __TIME__);
    /* To make the graphs random enough, give a different seed in each test case */
    srand(time(NULL));

#ifdef SPARSE
    genSparseRandGraph(G1_2D, n, degree);
#else
    genDenseRandGraph(G2_2D, n, prob);
#endif

    /* Following loop for different s,t pairs. */
    for (; test_cases_st <= NUM_ITERATIONS; test_cases_st++)
    {
        s = rand() % n + 1; // random selection of source node [0,5000]
        t = rand() % n + 1; // random selection of dest node [0,5000]

        printf("\r\n== \r\n");
        printf("Iteration #%d\r\n", test_cases_st);
        printf("Source s=%d && Destination t=%d\r\n", s, t);

#ifdef SPARSE
        addWeightsEdges(G1_2D, G1, s, t);
#else
        addWeightsEdges(G2_2D, G2, s, t);
#endif

#ifdef SPARSE
        // Test Djikstra using non heap structure
        printf("\r\n");
        printf("DJIKSTRA USING NON HEAP \r\n");
        test_djikstra_NonHeap(G1, s, t);

        // Test Djikstra using head structure
        printf("\r\n");
        printf("DJIKSTRA USING HEAP \r\n");
        test_djikstra_Heap(G1, s, t);

        // Test Kruskal using heap structure
        printf("\r\n");
        printf("KRUSKAL USING HEAP \r\n");
        test_kruskal_Heap(G1, s, t);
#else

        // Test Djikstra using non heap structure
        printf("\r\n");
        printf("DJIKSTRA USING NON HEAP \r\n");
        test_djikstra_NonHeap(G2, s, t);

        // Test Djikstra using head structure
        printf("\r\n");
        printf("DJIKSTRA USING HEAP \r\n");
        test_djikstra_Heap(G2, s, t);

        // Test Kruskal using heap structure
        printf("\r\n");
        printf("KRUSKAL USING HEAP \r\n");
        test_kruskal_Heap(G2, s, t);
#endif
    }

    return 0;
}
