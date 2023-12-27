#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#define NO_VISITADO -1
#define arista pair<int, int>

using namespace std;
vector<int> dfs_low, dfs_num, padre;
arista aristaIgnorada;
vector<arista> claves; //Almacena las aristas clave
vector<vector<int> > ady;
int C, M, N, contDFS, cantAristasPuente;

/* Definiciones:
 *  G=(V, E) es Sistema Fragil si existe arista(puente) vw tq G' = (V, E - {vw}) no es conexo.
 *  G es Robusto si no es Fragil
 *  Un enlace(arista vw de E) es clave si G'=(V, E-{vw}) es Fragil.
 * Se da:
 * 	N: cantidad de bases    <= 1e3
 *  M: cantidad de aristas  <= 2.1e3
 *  M aristas v w
 * Se pide:
 *  Dado G robusto determinar las aristas importantes
 *Idea:
 * Tenemos una funcion dfs que detecta la cantidad de aristas puente cant
 * Por cada arista vw en E, vw(almacenada en aristaAIgnorar): O(M)
 *  Corremos DFS                         -> O(M+N)
 *  Si cant != 0, entonces vw es clave.
 *      Agregar vw a S                   -> O(1)
 * Devolver S
 * Ordenamos S  -> O(M log M)
 */

void dfs(int u) { //Visto en una referencia de la practica
    dfs_low[u] = dfs_num[u] = contDFS++; // dfs_low[u] <= dfs_num[u]
    for(int v : ady[u]){
        arista e = {min(u, v), max(u, v)};
        if(e == aristaIgnorada) continue;
        if (dfs_num[v] == NO_VISITADO){ // Arista del arbol DFS
            padre[v] = u;
            dfs(v);
            if (dfs_low[v] > dfs_num[u]) //Condicion para saber si una arista es puente
                cantAristasPuente++;
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if (v != padre[u]) // Tenemos backEdge
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
    }
}

void solve(){
    for(int u = 0; u < N; u++) {
        for (int v: ady[u]) {
            aristaIgnorada = {min(u, v), max(u, v)};
            cantAristasPuente = contDFS = 0;
            dfs_low = vector<int>(N, 0);
            dfs_num = vector<int>(N, NO_VISITADO);
            padre = vector<int>(N, -1);
            dfs(u);
            if (cantAristasPuente != 0) {
                claves.push_back(aristaIgnorada);
            }
        }
    }
    sort(claves.begin(), claves.end());
    int cant = claves.size();
    cout << cant/2 << "\n";
    for(int i = 0; i < cant; i = i + 2) cout << claves[i].first << " "<< claves[i].second << "\n";
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.failbit); //Optimiza I/O de datos
    cin >> C;
    for(int c = 0; c < C; c++){
        cin >> N >> M;
        ady = vector<vector<int>>(N);
        claves.clear();
        for(int i = 0; i < M; i++){
            //Armamos el grafo
            int v, w;
            cin >> v >> w;
            ady[v].push_back(w);
            ady[w].push_back(v);
        }
        solve();
    }
}
