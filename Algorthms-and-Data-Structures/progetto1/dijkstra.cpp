using namespace std;
#include <fstream>
#include <vector>
#include <queue>

#define INFINITY 99999


struct nodo{
  vector<int> adj;
  int dist;
};

vector<nodo> grafo;

int N, M, Q;

void dijkstra(int G[max][max], int n, int startnode) {
   int cost[max][max], distance[max], pred[max];
   int visited[max], count, mindistance, nextnode, i, j;
   for(i = 0; i < n; i++)
      for(j = 0; j < n; j++)
        if(G[i][j] == 0)
          cost[i][j] = INFINITY;
   else
      cost[i][j] = G[i][j];
   for(i = 0; i < n; i++) {
      distance[i] = cost[startnode][i];
      pred[i] = startnode;
      visited[i] = 0;
   }
   distance[startnode]=0;
   visited[startnode]=1;
   count=1;
   while(count<n-1) {
      mindistance=INFINITY;
      for(i=0;i<n;i++)
         if(distance[i]<mindistance&&!visited[i]) {
         mindistance=distance[i];
         nextnode=i;
      }
      visited[nextnode]=1;
      for(i=0;i<n;i++)
         if(!visited[i])
      if(mindistance+cost[nextnode][i]<distance[i]) {
         distance[i]=mindistance+cost[nextnode][i];
         pred[i]=nextnode;
      }
      count++;
   }
   for(i=0;i<n;i++)
   if(i!=startnode) {
      cout<<"\nDistance of node"<<i<<"="<<distance[i];
      cout<<"\nPath="<<i;
      j=i;
      do {
         j=pred[j];
         cout<<"<-"<<j;
      }while(j!=startnode);
   }
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

  int G[N][N];

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      G[i][j] =
    }
  }
  dijkstra(G,N,u);

  for (int i = 0; i < Q; i++) {     //fa Q righe
    int a, b;
    in >> a >> b;
    out << dijkstra(G,N,a); << endl;
  }

  return 0;
}
