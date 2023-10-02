#include <iostream>
#include <vector>
#include <set>
#include <utility> //pair
using namespace std;
int c, M, N;
vector<set<int> > ady;
//DFS:
vector<vector<int>> tree_edges;
const int NO_LO_VI = 0, EMPECE_A_VER = 1, TERMINE_DE_VER = 2;
vector<int> estado(N, NO_LO_VI);
vector<int> back_edges_con_extremo_inferior_en;
vector<int> back_edges_con_extremo_superior_en;
//cubren:
vector<int> memo;
//RES:
set<pair<int,int>> claves;


void dfs(int v, int p) {
    estado[v] = EMPECE_A_VER;
    estado = vector<int>(N, NO_LO_VI);
    for(int u: ady[v]) {
        if(estado[u] == NO_LO_VI){
            tree_edges[v].push_back(u);
            dfs(u,v);
        } else if (u != p){
            if(estado[u] == EMPECE_A_VER)
                back_edges_con_extremo_inferior_en[v]++;
            else
                back_edges_con_extremo_superior_en[v]++;
        }
    }
    estado[v] = TERMINE_DE_VER;
}

int cubren(int v, int p){
    if(memo[v] != -1) return memo[v];
    int res = 0;
    for(int hijo : tree_edges[v]){
        if(hijo != p){
            res += cubren(hijo,v);
        }
    }
    res -= back_edges_con_extremo_superior_en[v];
    res += back_edges_con_extremo_inferior_en[v];
    memo[v] = res;
    return res;
}

void solve(){
    //Para cada arista sacarla
    for(int v=0; v<N; v++){
        for(int w: ady[v]){
            back_edges_con_extremo_inferior_en = vector<int>(N,0);
            back_edges_con_extremo_superior_en = vector<int>(N,0);
            tree_edges.clear();
            ady[v].erase(w);
            ady[w].erase(v);
            dfs(v, -1);
            memo = vector<int>(N, -1);
            int cantPuentes = cubren(v, -1);
            if(cantPuentes == 0){
                //es puente
                //entonces v-w es clave. la guardo
                //hay q asegurarse de no insertarla doble pues v-w = w-v.
                // si siempre agarramos la mas chica no se va a insertar doble. pq claves es un set
                if(v < w){
                    claves.insert(make_pair(v,w));
                }else{
                    claves.insert(make_pair(w,v));
                }
            }//sino, no es clave
            ady[v].insert(w);
            ady[w].insert(v);
            //puede que se rompa, pues estamos sacando y agregando algo en lo que estamos indexando
            //que pasa entonces con el for(int w : ady[v]) ? que me asegura que ahora q inserto de nuevo no va a volver a agarrar el mismo ? o que quede en loop
        }
    }
    //en caso de q ande bien, aca se imprime
    cout << claves.size() << endl;
    for(auto arista : claves){
        cout << arista.first << " " << arista.second << endl;
    }


    //Correr DFS
    //Correr cubren
}

int main(){
    cin >> c;
    for(int i=0; i<c; i++){
        cin >> M >> N;
        ady = vector<set<int>>(N);
        claves.clear();
        for(int k=0; k<M; k++){
            //Armamos el grafo
            int v, w;
            cin >> v >> w;
            ady[v].insert(w);
            ady[w].insert(v);
        }
        solve();
    }

}