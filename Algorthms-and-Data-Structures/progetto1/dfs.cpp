#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#include <stack>
using namespace std;


struct nodo{
  vector<int> adj;
  int dist = -1;
};

vector<nodo> grafo;

int N, M, Q;

int dfs(int a, int b){
  stack<int> st;
  st.push(a);
  while(!st.empty()){
    int n = st.top();
    st.pop();
    //Visita tutti i vicini
    for(int v:grafo[n].adj){
      if (v == b){
        return grafo[v].dist + 1;
      }else
      if (grafo[v].dist == -1){
        grafo[v].dist = grafo[n].dist + 1;
        st.push(v);
      }
    }
  }
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
  for (int i = 0; i < Q; i++) {     //fa Q righe
    int a, b;
    in >> a >> b;
    out << dfs(a, b) << endl;
  }

  return 0;
}
