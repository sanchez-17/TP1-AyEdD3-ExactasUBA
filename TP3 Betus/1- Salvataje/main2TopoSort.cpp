/*
 * El grafo es un DAG, podemos calcular el camino minimo del nodo 0(la salida) a todos los demas
 * en tiempo lineal O(m+n). Previamente ordenamos los nodos con topologicalSort.
 */
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
int N, M;
const int INF = 1e6;
vector<vector<pair<int,int>>> ady;
stack<int> cola;
vector<bool> visitado;
vector<int> dist;

void topologicalSort(int w) {
    visitado[w] = true;
    for (auto it: ady[w]) {
        int v = it.first;
        if (!visitado[v]) {
            topologicalSort(v);
        }
    }
    cola.push(w);
}

void solve(){
    for (int i = 0; i < 4*N+2; i++) {
        if (!visitado[i]) {
            topologicalSort(i);
        }
    }
    dist[0] = 0;
    while (!cola.empty()) {
        int w = cola.top(); cola.pop();
        for (auto it: ady[w]) {
            int v = it.first;
            int wt = it.second;
            dist[v] = min(dist[v],wt + dist[w]);
        }
    }
}

int main(){
    int c;
    cin>>c;
    for (int i = 0; i < c; ++i) {
        cin >> N >> M;
        ady = vector<vector<pair<int,int>>>(N*4 + 2); // Grafo triplicado + los vertice dummy
        for (int j = 0; j < M; ++j) { // Indices de pasadizos
            int u, v ;
            cin >> u >> v;
            for (int k = 0; k < 3; ++k) { // Conecta cada salon con su pasadizo
                ady[u + N*k].push_back({v+N*(k+1),2}); // Peso = 2min
            }
        }
        for (int u = 1; u < N; ++u) { // Conecta cada salon con su siguiente u->u+1
            for(int k = 0; k < 3; ++k)
                ady[u + N*k].push_back({u + N*k + 1,1}); // Peso = 1min
        }

        for(int k = 1; k < 5; ++k){//Conectamos los ultimos nodos de cada nivel con el ultimo salon
            ady[ N*k ].push_back({4*N+1,0});
        }
        //Conectamos el vertice de salida al primer salon
        ady[0].push_back({1, 1});

        visitado = vector<bool>(4*N + 2,false);
        dist = vector<int>(4*N + 2, INF);
        solve();
        cout << dist[4*N+1] << "\n";
    }

};
