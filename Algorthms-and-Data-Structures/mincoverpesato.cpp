using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <array>

struct nodo
{
    int padre;
    vector<int> adj;
};
vector<nodo> tree;
vector<vector<int>> D;
vector<int> peso;
int N;

int mincover(int node, int forced)
{
    if (D[node][forced] != -1){
        return D[node][forced];
    }
    int sol = peso[node];
    for (int i = 0; i < tree[node].adj.size(); i++)
    {
        sol += mincover(tree[node].adj[i], 0);
    }
    
    if (forced == 0){
        int sol2 = 0;
        for (int i = 0; i < tree[node].adj.size(); i++)
        {
            sol2 += mincover(tree[node].adj[i], 1);
        }
        sol = min(sol, sol2);
    }
    D[node][forced] = sol;
    return sol;
}

int main(void)
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N;
    tree.resize(N);
    D.resize(N, vector<int>(2, -1));
    peso.resize(N);
    int a, b;
    for (int i = 0; i < N; i++)
    {
        in >> peso[i];
    }
    
    for (size_t i = 0; i < N - 1; i++)
    {
        in >> a >> b;
        tree[a].adj.push_back(b);
        tree[b].padre = a;
    }

    out << mincover(0, 0) << endl;

    return 0;
}
