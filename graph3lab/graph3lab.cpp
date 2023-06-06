#include <iostream>
#include <math.h>
#include <cstdlib>
using namespace std;

struct Point {
    double x, y;
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
        for (int i = 0; i < vernum; i++)
        {
            for (int j = 0; i < vernum; j++)
            {

            }
        }
    }
};

int main()
{
    int N = 15, K = 5;
    MGraph graph(N);

    cout << "test";
}