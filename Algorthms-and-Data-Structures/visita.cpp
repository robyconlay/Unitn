using namespace std;

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

struct nodo{
  vector<int> vic;
  bool visitato = false;
};
vector<nodo> grafo;
int visita(nodo &, int &);
int main() {

  int N, M, S;
  ifstream in("input.txt");
  in >> N >> M >> S;
  grafo.resize(N);
  for (size_t i = 0; i < M; i++) {
    int from, to;
    in >> from >> to;
    grafo[from].vic.push_back(to);
  }
  int numNodi = 1;
  numNodi = visita(grafo[S], numNodi);
  ofstream out("output.txt");
  out << numNodi << endl;
  return 0;
}

int visita(nodo & N, int & cont){
  if (!N.visitato){
    N.visitato = true;
    for (int i = 0; i < N.vic.size(); i++) {
      if (!grafo[N.vic[i]].visitato){
        visita(grafo[N.vic[i]], cont);
        cont++;
      }
    }
  }
  return cont;
}
