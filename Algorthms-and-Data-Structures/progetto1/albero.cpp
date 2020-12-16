#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;


struct nodo{
  vector<int> adj;
  bool visited = false;
};
struct tree{
  int value;
  vector<tree> parents;
};

vector<nodo> grafo;
vector<tree> Tree;

int N, M, Q;

int bfs(int a){         //a è nodo d'inizio

  Tree.resize(N);
  // coda per la visita
  queue<int> q;
  q.push(a);
  int cur;
  tree * root = new tree;     //nodo root
  root.parents = NULL;       //I'm (g)root
  root.value = a;
  tree * t;
  while(!q.empty()){
    cur = q.front();
    q.pop();
    vector<tree> parents = t.parents; //cazzate su cazzate
    t = new tree;                     //cercasi migliorie
    t.parents = parents;
    t.parents.push_back(cur);     //nuovo nodo ha stessi parents più 1 (cur)
    for(int vic: grafo[cur].adj){
      if(!grafo[vic].visited){
        grafo[vic].visited = true;
        q.push(vic);
        tree * p = new tree;
        p.parents = t.parents;      //problem: i want to pass by copy actually
        p.parents.push_back(vic);   //p.parents assume tutti i numeri di t.parents
        p.value = vic;             //e ci aggiunge vic
        Tree.insert(vic, p);       //molto x
      }                            //usare un array per tenere conto di quali sono i nodi?
    }                              //ad esempio Tree[a] è il nodo a
  }                                //semplifica LCA ma potrebbe essere migliorata
  return 0;                        //forse modificando le strutture nodo, tree o graph

}
void LCA(tree & t, tree a, tree b){   //non conta cicli
  int aMax = a.parents.size();      //altezza a
  int bMax = b.parents.size();      //altezza b
  int i = aMax, j = bMax;
  int hops = 0;                   //numero avi in comune
  while (a.parents[i--] == b.parents[j--] && i >= 0 && j >= 0) { //unsure about i-- and j-- here
    //i--;                                                       //but looks smarter
    //j--;
    hops++;
  }
  return aMax + bMax - (2 * hops);        //almeno questo è giusto
}                                         //easy

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

  tree * t = bfs(0);                //costruisce un albero attraverso la bfs

  for (int i = 0; i < Q; i++) {     //fa Q righe
    int a, b;
    in >> a >> b;
    out << LCA(t, a, b) << endl;    //trova Least Common Ancestor tra a e b
  }                                 //non ho idea del perchè gli passo anche un albero
                                    //forse dovrebbero essere tutti alberi

  return 0;                         //su questo non ci piove
}
