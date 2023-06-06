#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;

struct Point
{
    double x, y;
};

void buildCompleteGraph(const Point* points, int N, double** graph)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                graph[i][j] = 0;
            }
            else
            {
                graph[i][j] = sqrt(pow(points[i].x - points[j].x, 2));
            }
        }
    }
}

int main()
{
    const int N = 15, K = 5;
    Point points[N];

    for (int i = 0; i < N; i++)
    {
        cin >> points[i].x >> points[i].x;
    }
    cout << "teest";
}