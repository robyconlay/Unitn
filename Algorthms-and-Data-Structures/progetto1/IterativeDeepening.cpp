#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <stack>
using namespace std;

struct nodo{
  vector<int> adj;
  int dist;
};

vector<nodo> grafo;

int iterativeDeepening(int root, int goal);
int depthLimitedSearch(int nodo, int goal, int depth);

int mindist = -1;
int N, M, Q;

int main(void) {
  ifstream in("input0.txt");
  ofstream out("output0.txt");

  in >> N >> M >> Q;                //fa la prima righa
  grafo.resize(N);

  // lettura del grafo
  for(int i = 0; i < M; i++){       //fa M righe
    int f, t;                       //costruisce grafo non orientato
    in >> f >> t;
    grafo[f].adj.push_back(t);
    grafo[t].adj.push_back(f);
  }
  for (int i = 0; i < Q; i++) {     //fa Q righe
    int a, b;
    in >> a >> b;
    out << iterativeDeepening(a, b) << endl;
  }

  return 0;
}

int iterativeDeepening(int root, int goal){
  for (int depth = 1; root != goal; depth++){
    root = depthLimitedSearch(root, goal, depth);
  }
  return root;
}

int depthLimitedSearch(int nodo, int goal, int depth){
  if (depth >= 0){
    if (nodo == goal){
      return nodo;
    }
    for (int child: grafo[nodo].adj){
      depthLimitedSearch(child, goal, depth - 1);
    }
  }
}
