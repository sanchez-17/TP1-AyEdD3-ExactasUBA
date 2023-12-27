/*
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
#include <iostream>
#include <vector>
using namespace std;
int N, M;
const int INF = 1e6;
vector<vector<pair<int,int>>> aristas; // Vecino y peso
vector<int> dp;

int f(int w){
    if(w == 4*N )           return 0;
    if(aristas[w].empty() && w != 4*N)  return INF;
    if(dp[w] != -1)         return dp[w];
    int res = INF;
    for(auto v_in: aristas[w]){
        res = min(res, f(v_in.first) + v_in.second);
    }
    dp[w] = res;
    return dp[w];
}

int main(){
    int c;
    cin>>c;
    for (int i = 0; i < c; ++i) {
        cin >> N >> M;
        aristas = vector<vector<pair<int,int>>>(N*4 + 2); // Grafo triplicado + los vertice dummy
        for (int j = 0; j < M; ++j) { // Indices de pasadizos
            int u, v ;
            cin >> u >> v;
            u--;v--;
            for (int k = 0; k < 3; ++k) { // Conecta cada salon con su pasadizo
                aristas[v+N*(k+1)].push_back({u + N*k,2}); // Peso = 2min
            }
        }
        for (int u = 0; u < N-1; ++u) { // Conecta cada salon con su siguiente u->u+1
            for(int k = 0; k < 3; ++k)
                aristas[(u + N*k) +1].push_back({u + N*k,1}); // Peso = 1min
        }

        for(int k = 0; k < 4; ++k){//Conectamos los ultimos nodos de cada nivel con el nodo dummy
            aristas[4*N+1].push_back({(N-1)+ N*k,0});
        }
        //Conectamos el vertices dummy
        aristas[0].push_back({N*4, 1});

        dp = vector<int>(4*N+2,-1);
        //cout << "Comienzo en " << N*4 + 1;
        cout << f(N*4 + 1) << "\n";
    }

};
