using namespace std;
#include <iostream>
#include <fstream>
#include <vector>

struct nodo{
  vector<int> vic;
  bool visited = false;
};
vector<nodo> grafo;

int percorri(int [], int [], int [], int [], int [], int [], int, int);
int nNodi, nArchi;

int main() {
  ifstream in("input.txt");
  in >> nNodi >> nArchi;
  int s [nArchi], t [nArchi], w [nArchi];
  int f [nArchi], y [nArchi], n [nArchi];
  for (size_t i = 0; i < nArchi; i++) {
    in >> s[i] >> t[i] >> w[i] >> f[i] >> y[i] >> n[i];
  }

  grafo.resize(nNodi);
  for (size_t i = 0; i < nArchi; i++) {
    grafo[s[i]].vic.push_back(t[i]);
    grafo[t[i]].vic.push_back(s[i]);
  }
  int time = 0;
  for (int i = 0; i < nArchi; i++){
    if (s[i] == 0){
      cout << "time =" << endl;
      time = max(time, percorri(s, t, w, f, y, n, t[i], 0));
    }
  }

  ofstream out("output.txt");
  if (time != 0){
    out << time << endl;
  } else{
    out << "-1" << endl;
  }
  return 0;
}

int percorri(int s [] , int t [], int w [], int f [], int y [], int n [], int i, int now){
  int time = 0;
  if (w[i] <= y[i] && s[i] != nArchi){    //periodo di spegnimento è minore del tempo di percorrimento
    while (!(((now - f[i]) % (y[i] + n[i])) < (y[i] - w[i]))) { //calcolo tempo attuale rispetto al laser
      now++;
      cout << "now++" << endl;
    }
    for (int j = i; j < nArchi; j++) {    //trova prossimi corridoi percorribili
      if (t[i] == s[j]){  //&& !visited
        cout << "t[i] == s[j]" << endl;
        time += percorri(s, t, w, f, y, n, s[j], now + w[i]);
      }
      if (s[i] == t[j]){    // && !visited
        cout << "s[i] == t[j]" << endl;
        time += percorri(s, t, w, f, y, n, t[j], now + w[i]);
      }
    }
  }
  return time;
}

/*
if (0 not visited) visita 0
guarda 0.vic
entra in 0.vic[0]

visita 1
guarda 1.vic[0]
entra in 3

entra in 0.vic[1]

visita 2
guarda 2.vic[0]
entra in 3

bond va solo avanti, non ripercorre un arco

to solve: devo calcolare più percorsi, quindi visited deve venir cambiato in false di nuovo, più volte

*/
