#include <iostream>
#include <math.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#define INF DBL_MAX
using namespace std;

struct Point {
    double x, y;
    Point(double _x, double _y) : x(_x), y(_y) {}
    Point()
    {
        x = 1 + rand() % 100;
        y = 1 + rand() % 100;
    }
    static double distance(const Point p1, const Point p2)
    {
        return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    }
};

struct Edge
{
    int u, v;
    double weight;
    Edge(int _u, int _v, double _weight) : u(_u), v(_v), weight(_weight) {}
};

class MGraph
{
    double** weights;
    int vernum; //вершины
    vector<Point> vertexes;
public:
    MGraph(int _vernum): vernum(_vernum)
    {
        for (int i = 0; i < vernum; i++)
        {
            vertexes.push_back(Point());
        }

        weights = new double* [vernum];
        for (int i = 0; i < vernum; i++) {
            weights[i] = new double[vernum];
            for (int j = 0; j < vernum; j++) {
                weights[i][j] = INF; // Инициализируем все веса нулями
            }
        }
    }

    void buildCompleteGraph()
    {
        for (int i = 0; i < vernum; i++)
        {
            for (int j = 0; i < vernum; j++)
            {
                weights[i][j] = Point::distance(vertexes[i], vertexes[j]);
            }
        }
    }

    void add_edge(int u, int v)
    {
        weights[u][v] = Point::distance(vertexes[u], vertexes[v]);
    }

    //алгоритм примо
    vector<Edge> getSpanTree() {
        vector<Edge> EdgesOfTree;
        double wmin;
        int i, j, vm, * B = new int[vernum];
        B[0] = -1;
        for (i = 1; i < vernum; i++) B[i] = 0;
        for (i = 1; i < vernum; i++) {
            wmin = INF; vm = 0;
            for (j = 1; j < vernum; j++)
                if (B[j] != -1 && wmin > weights[j][B[j]])
                {
                    vm = j; wmin = weights[j][B[j]];
                }
            if (!vm) return EdgesOfTree;
            add_edge(vm, B[vm]);
            EdgesOfTree.push_back(Edge(vm, B[vm], weights[vm][B[vm]]));
            B[vm] = -1;
            for (j = 1; j < vernum; j++)
                if (B[j] != -1 && weights[j][B[j]] > weights[j][vm])
                    B[j] = vm;
        }
        return EdgesOfTree;
    }
};

int main()
{
    int N = 15, K = 5;
    MGraph graph(N);
    graph.buildCompleteGraph();

    vector<Edge> OstovGraph = graph.getSpanTree(); // выделение минимального остова

    sort(OstovGraph.begin(), OstovGraph.end()); //отсортировать ребра остова по возрастанию весов.

    bool** adj = new bool* [N];
    for (int i = 0; i < N; i++)
    {
        adj[i] = new bool[N];
        for (int j = 0; j < N; j++)
        {
            adj[i][j] = 0;
        }
    }
}