#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef int lmao;

struct nodo{
  vector<lmao> adj;
  bool visited = false;
  vector<lmao> parents;
  lmao value;
};

vector<nodo> grafo;

int N, M, Q;

void bfs(int a){         //a è nodo d'inizio
  queue<int> q;
  q.push(a);
  grafo[a].visited = true;
  grafo[a].value = a;
  int cur;
  while(!q.empty()){
    cur = q.front();
    q.pop();
    for(int vic: grafo[cur].adj){
      if(!grafo[vic].visited){
        grafo[vic].visited = true;
        q.push(vic);
        if (cur != 0){
          grafo[vic].parents = grafo[cur].parents;
        }
        grafo[vic].parents.push_back(cur);
        grafo[vic].value = vic;
      }
    }
  }
}

int LCA(nodo &a, nodo& b){            //non conta cicli
  int aMax = a.parents.size();      //altezza a
  int bMax = b.parents.size();      //altezza b
  if (aMax == 0 || bMax == 0){
    return aMax + bMax;
  }
  int i = 0, j = 0;
  int hops = 0;                   //numero avi in comune
  for (int adj: a.adj)            //look if a.adjacent are b
    if (adj == b.value)
      return 1;
  while (a.parents[i] == b.parents[i] && i < aMax && i < bMax) {        //check
    hops++;
  }
  if (a.value == b.parents[i] || b.value == a.parents[i]){
    hops++;
  }
  return aMax + bMax - (2 * (hops - 1));
}


int main(void) {
  ifstream in("input0.txt");
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

  bfs(0);               //costruisce un albero attraverso la bfs

  for (int i = 0; i < Q; i++) {     //fa Q righe
    int a, b;
    in >> a >> b;
    out << LCA(grafo[a], grafo[b]) << endl;   //trova Least Common Ancestor tra a e b
  }
  return 0;
}
