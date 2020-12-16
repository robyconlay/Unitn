using namespace std;

#include <iostream>
#include <fstream>
#include <vector>
//#include "tsp.h"

struct node
{
    int id;
    vector<int> adj;
    bool visited = false;
};

vector<node> graph;

void solve(int N, int **w)
{


}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int N;
    in >> N;
    int w[N][N];
    //cout << "N is: " << N << endl;
    graph.resize(N);
    for (int i = 0; i < N; i++)
    {
        graph[i].adj.resize(N, -1);
    }
    for (int i = 0; i < N; i++)
    {
        graph[i].id = i;
        for (int j = 0; j < N; j++)
        {
            if (i != j)
            {
                graph[i].adj.push_back(j);
            }
        }
    }

    for (int i = 0; i < N - 1; i++)
    {
        int weight;
        for (int j = 0; j <= i; j++)
        {
            in >> weight;
            w[i + 1][j] = weight;
            w[j][i + 1] = weight;
            //cout << "from " << i + 1 << " to " << j << " weights: " << weight << endl;
        }
        //cout << "here" << endl;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == j)
            {
                cout << "\t";
            }
            else
            {
                cout << w[i][j] << "\t";
            }
        }
        cout << endl;
    }
    solve(N, w);
    out << "#";

    return 0;
}
