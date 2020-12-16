#include <fstream>
#include <iostream>
using namespace std;

unsigned short int N, M, Q;

int visit(unsigned short int a, unsigned short int b, unsigned short int matrix[][]){
  queue<short int> q;
  if (matrix[a][b] == 1){
    return 1;
  }
  for (size_t i = 0; i < N; i++) {
    if (matrix[a][i] == 1){
      q.push(i);
    }
  }
  for (size_t i = 0; i < N; i++) {
    return 1 + visit(i, b, matrix);
  }
}

int main(void) {
  ifstream in("input.txt");
  ofstream out("output.txt");

  in >> N >> M >> Q;                //fa la prima righa
  grafo.resize(N);
  short int matrix[N][N];
  for (int i = 0; i < N; i++) {    //initialization
    for (int j = 0; j < N; j++) {
      matrix[i][j] = 0;
    }
  }
  // lettura del grafo
  for(int i = 0; i < M; i++){
    unsigned shirt f, t;                       //costruisce grafo non orientato
    in >> f >> t;
    matrix[f][t] = 1;
  }

  for (int i = 0; i < Q; i++) {     //fa Q righe
    int a, b;
    in >> a >> b;
    out << bfs(a, b) << endl;
  }

  return 0;
}
