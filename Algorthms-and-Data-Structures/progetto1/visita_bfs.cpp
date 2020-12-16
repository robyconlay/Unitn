#include <fstream>
#include <vector>
#include <queue>
using namespace std;


struct nodo{
  vector<int> adj;
  bool visited=false;
  int dist;
};

vector<nodo> grafo;
int count=0;

int main(void)
{
  ifstream in("input.txt");
  ofstream out("output.txt");
  int N,M,S;
  in >> N >> M >> Q;
  grafo.resize(N);
  //Lettura del grafo
  for(int i = 0; i < M; i++){
    int f, t;
    in >> f >> t;
    grafo[f].adj.push_back(t);
    grafo[t].adj.push_back(s);
  }

  queue<int> q;
  q.push(Q);
  while(!q.empty()){
    int n = q.front();
    q.pop();
    //Se abbiamo giá visitato il nodo, ignoriamolo.
    if(grafo[n].visited)
      continue;
    grafo[n].visited=true;
    //Aumenta il contatore
    count++;
    //Visita tutti i vicini
    for(int v:grafo[n].adj)
      q.push(v);
  }

  out<<count<<endl;
  return 0;
}
