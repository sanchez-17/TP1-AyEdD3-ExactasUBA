#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#define UNVISITED -1
#define VISITED 1
#define arista pair<int, int>

using namespace std;
vector<int> dfs_low, dfs_num, padre;
vector<arista> claves; //Almacena las aristas clave
vector<vector<int>> AdjList;
int C, M, N, verticeAIgnorar, contDFS, raiz, hijosDeRaiz, cantAristasPuente;

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

void dfs(int u) {
    dfs_low[u] = dfs_num[u] = contDFS++; // dfs_low[u] <= dfs_num[u]
    for(int v : AdjList[u]){
        if((v == verticeAIgnorar && u == raiz) || (v == raiz && u == verticeAIgnorar)) continue;
        if (dfs_num[v] == UNVISITED){ // a tree edge
            padre[v] = u;
            if (u == raiz) hijosDeRaiz++; // special case if u is a root
            dfs(v);
            if (dfs_low[v] > dfs_num[u]) // for bridge
                cantAristasPuente++;
            dfs_low[u] = min(dfs_low[u], dfs_low[v]); // update dfs_low[u]
        }
        else if (v != padre[u]) // a back edge and not direct cycle
            dfs_low[u] = min(dfs_low[u], dfs_num[v]); // update dfs_low[u]
    }
}

void solve(){
    //Por cada arista en E

    for(int u = 0; u < N; u++) {
        for (int v: AdjList[u]) {
            cantAristasPuente = 0;
            contDFS = 0;
            hijosDeRaiz = 0;
            dfs_low = vector<int>(N);
            dfs_num = vector<int>(N);
            raiz = u;
            padre = vector<int>(N, -1);
            verticeAIgnorar = v;
            dfs(u);
            if (cantAristasPuente != 0) {
                arista clave = {min(u, v), max(u, v)};
                claves.push_back(clave);
            }

        }
    }
    sort(claves.begin(), claves.end());
    cout << claves.size() << endl;
    if(claves.size()!=0){
        cout << claves[0].first << claves[0].second << endl;
    }
    for(int i = 1; i < claves.size();i++ ){
        if(claves[i-1]==claves[i]){
            continue;
        }
        cout << claves[i].first << claves[i].second << endl;
    }
}

int main(){
    cin >> C;
    for(int c = 0; c < C; c++){
        cin >> N >> M;
        AdjList = vector<vector<int>>(N);
        claves.clear();
        for(int i = 0; i < M; i++){
            //Armamos el grafo
            int v, w;
            cin >> v >> w;
            AdjList[v].push_back(w);
            AdjList[w].push_back(v);
        }
        solve();
    }
}
