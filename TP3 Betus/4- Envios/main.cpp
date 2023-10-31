#include <algorithm>
#include <iostream>
#include <vector>
#define arista pair<int, int>
using namespace std;
vector<vector<int>> capacidades;
vector<vector<arista>> ady;
/* Cada calle es una arista de capacidad c(e)
 * Dado un valor C, la cantidad max. de herramientas que puede llevar cada persona es div_entera(c(e), C).
 * Ejemplo: para un calle e, c(e) = 13. C = 5. div_entera(13,2) = 2
 * Es decir, fijamos un valor C. Y modelamos las aristas como div_entera(c(e), C) para toda arista e en G.
 * Luego calculamos flujo maximo. Hacemos busqueda binaria de C con la siguiente propiedad binaria:
 * "Si x personas pueden transportar C objetos por G hasta t, pueden transportar C-1"
 * Entrada:
 *  N : Cant de esquinas     1 <= N <= 1e2
 *  M : Cant de calles e     1 <= M <= 1e3
 *  x : Cant de personas     1 <= x <= 1e6
 *  Luego M lineas de calle e = v, w, c donde:   //Las calles tienen direccion
 *     v : esquina de origen
 *     w : esquina de destino
 *     c : capacidad de la calle   1 <= c <= 1e6
 *
 */

int EyK(int s, int t){
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacidades[prev][cur] -= new_flow;
            capacidades[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

void busqueda_binaria(long double a, long double b){
    int cont = 0;
    while(cont < 50 ){
        // para salvar casos como el de la diapo
        cont++;
        long double mid =(a+b)/2;
        //con las aristas creamos nuevas para el kruskal (usa vector tripla)
        for (Arista& e: aristas)
            e.w = mid * e.r - e.d; //Actualizo el nuevo peso de las aristas
        if(EyK(0,N-1)){
            a = mid;
            Dmax = D;
            Rmax = R;
        }else{ //cuando es mayor, quiero uno mas chico
            b=mid;
        }
    }
}

void solve(){

}

int main(){
    int C,N,M;
    cin >> C;
    while(C>0){
        cin >> N >> M;
        capacidades = vector<vector<int>>(N, vector<int>(N, 0));
        ady = vector<vector<arista>>(N+2);
        for(int i = 0; i < M; i++){
            int v, w, c;
            cin >> v >> w >> c;
            v--; w--;
            ady[v].push_back({w,c});
        }
        //Modelado del grafo


        solve();
        C--;
    }
    return 0;
}




