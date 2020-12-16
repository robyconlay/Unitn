#include <bits/stdc++.h>
#include "tsp.h"
#define MAXN 50
#define MAXW 1000
using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

struct node{
    int id;
    vector<int> adj;
    bool visited = false;
};

int N;
vector<node> graph;

void solve(){ 
	int bestsol = MAXW*MAXN;
	while(true){
		int source = rand()%N;
		queue<int> q;
		q.push(source);

		int currentsol = 0;
		vector<int> sol;
		while(!q.empty()){
			int v = q.front();
			q.pop();
			sol.push_back(v);
			int minu = -1, mindistance = MAXW;
			for(int u = 0; u<N; u++){
				if((graph[v].adj)[u]<mindistance && !graph[u].visited && u!=v){
					minu = u;
					mindistance = graph[v].adj[u];
				}
			}
			graph[v].visited = true;

			// aggiungo passaggio in un nodo random ogni tanto
			if(rand()%3 == 0){
				int randu = rand()%N;
				if(!graph[randu].visited && randu != v) minu = randu;
			}
			
			if(minu != -1)
				q.push(minu);

			currentsol += (graph[v].adj)[minu];
		}
		if(currentsol < bestsol){
			for(int i = 0; i<N; i++){
				out << sol[i] << " ";
			}
			out << source << "#" << endl;
			bestsol = currentsol;
		}
		for(int i = 0; i<N; i++){
			graph[i].visited = false;;
		}
	}
} 

int main() {

	srand(time(NULL));

    in >> N;
    graph.resize(N);
    
    int w;
    for (int i = 0; i<N; i++){
    	(graph[i].adj).resize(N);
        for (int j = 0; j<i; j++){
            in >> w;
            (graph[i].adj)[j] = w;
            (graph[j].adj)[i] = w;
        }
    }

    solve();

    return 0;
}
