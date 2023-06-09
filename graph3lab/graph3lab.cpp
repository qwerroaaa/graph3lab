﻿#include <iostream>
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
        x = rand()%100 + 1;
        y = rand()%100 + 1;
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
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }

};

class MGraph
{
    double** weights;
    int vernum; //вершины
    vector<Point> vertexes;
    int comptotal;
public:
    MGraph(int _vernum): vernum(_vernum), comptotal(0)
    {
        for (int i = 0; i < vernum; i++)
        {
            vertexes.push_back(Point());
        }

        weights = new double* [vernum];
        for (int i = 0; i < vernum; i++) {
            weights[i] = new double[vernum];
            for (int j = 0; j < vernum; j++) {
                weights[i][j] = INF;
            }
        }
    }

    void buildCompleteGraph()
    {
        for (int i = 0; i < vernum; i++)
        {
            for (int j = 0; j < vernum; j++)
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
        double wmin; //переменная для минимального веса ребра
        int i, j, vm, * B = new int[vernum]; //массив B для снижения трудоемкости
        B[0] = -1; //вершина уже включена в ребро
        for (i = 1; i < vernum; i++) B[i] = 0;
        for (i = 1; i < vernum; i++) {
            wmin = INF; vm = 0;
            for (j = 1; j < vernum; j++)
                if (B[j] != -1 && wmin > weights[j][B[j]])
                {
                    vm = j; wmin = weights[j][B[j]]; //поиск минимального ребра среди непосещенных
                }
            if (!vm) return EdgesOfTree; //возвращения пустого вектора //если vm = 0, то нет следующей вершины для включения в остовное дерево
            add_edge(vm, B[vm]);
            EdgesOfTree.push_back(Edge(vm, B[vm], weights[vm][B[vm]])); //ребро между vm and B with weights
            B[vm] = -1; //помечаем, что прошли
            for (j = 1; j < vernum; j++)
                if (B[j] != -1 && weights[j][B[j]] > weights[j][vm]) //определяем не является ли вершина вершина vm близжайщей соседней к j
                    B[j] = vm; //если 𝑖 – ближайшая к  𝑗 уже включенная в остов вершина.

        }
        return EdgesOfTree; //возвращаем остовной граф
    }

   


    Point getVertex(int index)
    {
        return vertexes[index];
    }
};

void dfs(int vertex, int* visited, vector<int>* components, int current_component, bool** adj, int N) {
    // устанавливает номер текущей компоненте связанной вершине, если 1, то посетили, если 0, то нет
    visited[vertex] = 1;
    // считаем количество вершин в компонентах
    components[current_component - 1].push_back(vertex);

    // ищем соседей
    for (int i = 0; i < N; i++)
    {
        if (visited[i] == 0 && adj[vertex][i]) { //прошли ли мы i и есть ли ребро vertex i
            dfs(i, visited, components, current_component, adj, N);
        }
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    int N = 40, K = 8;
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
    

    for (int i = 0; i < N - K; i++) //строим смежную матрицу по N-K ребрам
    {
        adj[OstovGraph[i].u][OstovGraph[i].v] = 1;
        adj[OstovGraph[i].v][OstovGraph[i].u] = 1;
    }

    vector<int>* components = new vector<int>[K];
    int num_components = 0;

    // visited отображает номера компонент
    int* visited = new int[N];
    for (int i = 0; i < N; i++) {
        visited[i] = 0;
    }
     
    // ищим новые компоненты
    for (int i = 0; i < N; i++) {
        if (visited[i] == 0) {
            num_components++;// нашли новую компоненту
            dfs(i, visited, components, num_components, adj, N);
        }
    }


    for (int component = 0; component < K; component++)
    {
        double sumX = 0;
        double sumY = 0;
        double minX = INF;
        double minY = INF;
        double maxX = 0;
        double maxY = 0;
        int size = components[component].size();
        cout << "Компонента: " << component << "\nВключает в себя: " << size << " Вершин" << endl;
        for (int i = 0; i < size; i++)
        {
                Point currentPoint = graph.getVertex(components[component][i]);
                sumX += currentPoint.x;
                sumY += currentPoint.y;
                minX = min(minX, currentPoint.x);
                minY = min(minY, currentPoint.y);
                maxX = max(maxX, currentPoint.x);
                maxY = max(maxY, currentPoint.y);
               
        }
        double centroidX = sumX / size;
        double centroidY = sumY / size;

        cout << "Минимальные значения координат: (" << minX << ", " << minY << ")\n";
        cout << "Максимальные значения координат: (" << maxX << ", " << maxY << ")\n";
        cout << "Координаты центроиды: (" << centroidX << ", " << centroidY << ")\n";
        cout << "\n";
    }
}