#include <iostream>
#include <math.h>
#include <cstdlib>
#include <algorithm>

#define INF DBL_MAX
using namespace std;

struct Point {
    double x, y;
    Point()
    {
        x = 1 + rand() % 100;
        y = 1 + rand() % 100;
    }
    double distance(const Point p1, const Point p2)
    {
        return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    }
};

class MGraph
{
    double** weigths;
    int vernum; 
    bool oriented;
public:
    MGraph(int _vernum): vernum(_vernum)
    {
        //some code
    }

    void buildCompleteGraph()
    {
        double distance;
        for (int i = 0; i < vernum; i++)
        {
            for (int j = 0; i < vernum; j++)
            {
                weigths[i][j] = distance;
            }
        }
    }

    void get_span_tree() {
        double wmin;
        int i, j, vm, * B = new int[vernum];
        B[0] = -1;
        for (i = 1; i < vernum; i++) B[i] = 0;
        for (i = 1; i < vernum; i++) {
            wmin = INF; vm = 0;
            for (j = 1; j < vernum; j++)
                if (B[j] != -1 && wmin > weigths[j][B[j]])
                {
                    vm = j; wmin = weigths[j][B[j]];
                }
            if (!vm) return;
            add_edge(vm, B[vm]); B[vm] = -1;
            for (j = 1; j < vernum; j++)
                if (B[j] != -1 && weigths[j][B[j]] > weigths[j][vm])
                    B[j] = vm;
        }
    }
};

int main()
{
    int N = 15, K = 5;
    MGraph graph(N);



    bool** adj = new bool* [N];
    for (int i = 0; i < N; i++)
    {
        adj[i] = new bool[N];
        for (int j = 0; j < N; j++)
        {
            adj[i][j] = 0;
        }
    }

    cout << "test";
}