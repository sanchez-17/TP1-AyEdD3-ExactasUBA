#include <algorithm>
#include <iostream>
#include <vector>
#define arista pair<int, int>
using namespace std;
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

void solve(){

}

int main(){
    int C,N,M;
    cin >> C;
    while(C>0){
        cin >> N >> M;
        ady = vector<vector<arista>>(N);
        for(int i = 0; i < M; i++){
            int v, w, c;
            cin >> v >> w >> c;
            ady[v].push_back({w,c});
        }
        solve();
        C--;
    }
    return 0;
}



