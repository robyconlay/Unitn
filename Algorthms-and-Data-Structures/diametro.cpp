using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <queue>

struct nodo{
  vector<int> vic;
  bool visitato = false;
};
vector<nodo> grafo;
void erdos(vector<nodo> grafo, nodo r);

int main() {
  int N, M;

  ifstream in("input.txt");
  in >> N >> M;
  grafo.resize(N);
  for (size_t i = 0; i < M; i++) {
    int from, to;
    in >> from >> to;
    grafo[from].vic.push_back(to);
    grafo[to].vic.push_back(from);
  }

  int count = 0;
  for (size_t i = 0; i < N - 1; i++) {
    count = max(count, conteggio(grafo, grafo[i], 0));
  }

  ofstream out("output.txt");
  out << count << endl;
  return 0;
}

void erdos(vector<nodo> grafo, nodo r){
  int[] erdos;
  nodo[] parent;
  queue Q;
  Q.push(r);
  for(nodo u: grafo){
    erdos[u] = -10000;
  }
  erdos[r] = 0;
  parent[r] = NULL;
  while(!Q.empty()){
    nodo u = Q.pop();
    for(int v: u.vic){
      if (erdos[v] == -10000){
        erdos[v] = erdos[u] + 1;
        parent[v] = u;
        Q.pop();
      }
    }
  }
}
