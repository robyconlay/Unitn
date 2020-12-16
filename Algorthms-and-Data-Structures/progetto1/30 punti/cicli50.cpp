#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct nodo{
  vector<int> adj;
  bool visited = false;
  vector<int> parents;
  int value;
  vector<int> accesso_cricche;
};

vector<nodo> grafo;
vector<vector<int>> cricche;

int N, M, Q;

vector<int> cercaCiclo(nodo partenza){
  vector<int> cicli;
  cicli.push_back(partenza.value);
  for (int vic: partenza.adj){
    for (int adj: grafo[vic].adj){
      if (grafo[adj].visited && adj != grafo[vic].parents[grafo[vic].parents.size()]){
        cicli.push_back(adj);
      }
    }
  }
  return cicli;
}

void bfs(int a){         //a è nodo d'inizio
  int numCiclo = 0;
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
      } else if (vic != cur){                       //c'è un ciclo se esiste un nodo adiaciente
        vector<int> ciclo = cercaCiclo(grafo[vic]);
        cricche.push_back(ciclo);              //già visitato che non è parent
        grafo[cur].accesso_cricche.push_back(vic);
      }                                         //cricche[numCiclo].push_back(&ciclo);
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
    if (cricche.size() != 0 && a.parents[i] == a.accesso_cricche[j]){       //se ci sono cricche
      for (int match : b.accesso_cricche){              //e se il parent analizzato fa parte di una
        if (match == a.accesso_cricche[j]){             //se il nodo di accesso di a e b
          return aMax + bMax - (2 * i);                 //al ciclo sono gli stessi
        }else {
          for (int nodi : cricche[j]){
            if (nodi == match){          //se tra i nodi della cricca si trova un nodo di accesso di b
              return aMax + bMax - (2 * i) + 1;         //(oppure) se b è collegato allo stesso ciclo
            }
          }
        }
      }
    }
  }
  if (a.value == b.parents[i] || b.value == a.parents[i]){
    hops++;
  }
  return aMax + bMax - (2 * (hops - 1));
}


int main(void) {
  ifstream in("input3.txt");
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
