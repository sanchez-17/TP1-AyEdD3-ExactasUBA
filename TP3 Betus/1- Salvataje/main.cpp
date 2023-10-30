/*
 * Idea:
 *  Duplicar el grafo G 3 veces, conectados a traves de los tuneles
 *  Si en G habia un tunel que iba del nodo i a j
 *  En G' el tunel seran 3 tuneles que conecten v_(i+4k) con v_(j+4(k+1)) para 0 <= k < 3
 *  si habia un tunel que iba del nodo v a w, entonces agregamos una arista v->w+4 y 4k*v+1->w+4k 1<=k<3
 *  luego los nodos v_n los conectamos a un nodo dummy d con aristas de peso 0.
 *  Como G' es DAG, calculamos camino minimo desde v_0 a d en O(n). con esta funcion
 *
 *        | 0                                   si w=v_0
 * f(w) = |  min{z in N_in(w)}_{f(z) + w(z->w)}  cc
 *        |
 *
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int N, M;
vector<vector<pair<int,int>>> aristas; // Vecino y peso

int main(){
    int c;
    cin>>c;
    for (int i = 0; i < c; ++i) {
        cin >> N >> M;
        aristas = vector<vector<pair<int,int>>>(N*4 + 2); // Grafo triplicado + los vertice dummy
        for (int j = 0; j < M; ++j) { // Indices de pasadizos
            int u, v;
            cin>>u>>v;

            for (int k = 0; k < 3; ++k) { // Conecta cada salon con su pasadizo. k <4??
                aristas[u + 4*k].push_back({v+4*(k+1),2}); // Peso = 2min
            }

            for (int w = 0; w < N; ++w) { // Conecta cada salon con su siguiente
                for(int k = 0; k < 3; ++k)
                    aristas[w].push_back({w+1,1}); // Peso = 1min
            }
        }
        //Conectamos los vertices dummy
        aristas[N*4].push_back({0, 1});
        for(int k = 0; k < 4; ++k){
            //aristas[N*4*k -1]
        }
    }

};
