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

/*
 * El grafo es un DAG, podemos calcular el camino minimo del nodo 0(la salida) a todos los demas
 * en tiempo lineal O(m+n). Previamente ordenamos los nodos con topologicalSort.
 * Idea:
 *  Duplicar el grafo G 3 veces, conectados a traves de los tuneles
 *  Si en G habia un tunel que iba del nodo i a j
 *  En G' el tunel seran 3 tuneles que conecten v_(i+N*k) con v_(j+N(k+1)) para 0 <= k < 3
 *  si habia un tunel que iba del nodo v a w, entonces agregamos una arista v->w+N y N*k*v+1->w+Nk 1<=k<3
 *  luego los nodos v_n los conectamos a un nodo dummy d con aristas de peso 0.
 *  Como G' es DAG, calculamos camino minimo desde v_0 a d en O(n). con esta funcion
 *
 *  Nota: invertimos las aristas del grafo G'
 *
 *        | 0                                   si w=v_0
 *        | INF                                 si N_in(w)=vacio y w != v_0
 * f(w) = |  min{z in N_in(w)}_{f(z) + w(z->w)}  cc
 *        |
 *
 */
 

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
    cin >> c;
    for(int i = 0; i < c; i++){
        cin >> N >> M;
        ady = vector<vector<pair<int, int>>>(N*4 + 2);
        dist = vector<int>(N*4 + 2, INF);
        visitado = vector<bool>(N*4 + 2, false);
        // Uno los vertices dummy 0 y N*4 + 1.
        for(int k = 0; k < 4; k++){
            ady[0].push_back({1 + N*k, 1});
            ady[N + N*k].push_back({N*4 + 1,0});
        }

        // Uno los salones. Como son 4 niveles los puedo unir de la sig forma:
        for(int j = 1; j < N; j++){
            ady[j].push_back({j+1, 1});
            ady[j + N].push_back({j + N + 1, 1});
            ady[j + N*2].push_back({j + N*2 + 1, 1});
            ady[j + N*3].push_back({j + N*3 + 1, 1});
        }

        // Ingreso y voy uniendo los puentes. Nuevamente, como son 4 niveles, los puedo unir de la sig forma:
        for(int puente = 0; puente < M; puente++){
            int u, v;
            cin >> u >> v;
            ady[u].push_back({v + N, 2});
            ady[u + N].push_back({v + N*2, 2});
            ady[u + N*2].push_back({v + N*3, 2});
        }
        solve();
        cout << dist[N*4 +1] << endl;
    }
    return 0;
}
