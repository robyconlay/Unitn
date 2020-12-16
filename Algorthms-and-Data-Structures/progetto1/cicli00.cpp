#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;


struct nodo{
  vector<int> adj;
  int dist;
};

vector<nodo> grafo;

int N, M, Q;

int bfs(int a, int b){
  { // reset del problema
    // all'inizio ogni nodo ha distanza -1, a parte il nodo di partenza
    for(nodo& n:grafo)
      n.dist = -1;
    grafo[a].dist = 0;
  }

  // coda per la visita
  queue<int> q;
  q.push(a);
  int cur;
  while(!q.empty()){
    cur = q.front();
    q.pop();
    for(int vic: grafo[cur].adj){
      if (vic == b){
        return grafo[cur].dist + 1;
      }else
        if(grafo[vic].dist == -1){
          // se un vicino non é ancora stato visitato, imposto la sua distanza.
          grafo[vic].dist = grafo[cur].dist+1;
          q.push(vic);
      }
    }
  }
  return 0;
  // aggiorno la distanza massima con la distanza dell'ultimo nodo visitato
}

int main(void) {
  ifstream in("input.txt");
  ofstream out("output.txt");

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
    out << bfs(a, b) << endl;
  }

  return 0;
}
