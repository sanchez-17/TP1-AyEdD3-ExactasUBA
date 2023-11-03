#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int t, N, M, X;
const int INF = 1e9;
vector<vector<int>> capacidades;
struct Arista{
    Arista(int _v, int _c){
        v = _v; c = _c;
    }
    int v, c;
};
vector<vector<Arista>> ady;

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

 //version con busqueda binaria no dependiente de cant de iteraciones

 void actualizarPesosEnG(int c){
     //Actualizo las capacidades de las aristas a c(e)/C
     for(int i = 0; i < N; i++)
         for (Arista& e: ady[i]) {
             capacidades[i][e.v] = e.c / c;
             capacidades[e.v][i] = 0;
         }
 }

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (auto next : ady[u]) { //cur->next
            int v = next.v;
            if (parent[v] == -1 && capacidades[u][v]) {
                parent[v] = u;
                int new_flow = min(flow, capacidades[u][v]);
                if (v == t)
                    return new_flow;
                q.push({v, new_flow});
            }
        }
    }

    return 0;
}

int EyK(int s, int t){
    int flow = 0;
    vector<int> parent(N);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int v = t;
        while (v != s) {
            int u = parent[v];
            capacidades[u][v] -= new_flow;
            capacidades[v][u] += new_flow;
            v = u;
        }
    }

    return flow;
}

int busqueda_binaria(int a, int b){
     int C;
    while(b - a > 1){ //P(a) verdadero
        C =(a+b)/2;
        //Actualizo las capacidades de las aristas a c(e)/C
        actualizarPesosEnG(C);
        int flow = EyK(0,N-1);
        actualizarPesosEnG(1);
        if (flow < X)//P(C) falso: "Si x personas pueden transportar C objetos por G hasta t, pueden transportar C-1"
            b = C;
        else
            a = C;
    }
    return a; //El maximo valor de C que cumple P(C) es a
}

int solve(int cota){
    int flow = EyK(0,N-1), res;
    //Restauramos los valores iniciales de las capacidades
    actualizarPesosEnG(1);
    if(flow >= X) res = busqueda_binaria(0, 2*cota);
    else res = 0;
    return X * res;
}

int main(){
    cin >> t;
    while(t>0){
        cin >> N >> M >> X;
        capacidades = vector<vector<int>>(N, vector<int>(N, 0));
        ady = vector<vector<Arista>>(N);
        int maxPeso = 0;
        for(int i = 0; i < M; i++){
            int v, w, c;
            cin >> v >> w >> c;
            maxPeso = max(maxPeso, c);  //cota superior de la busqueda binaria
            v--; w--;
            Arista vw(w , c);
            //Arista wv(v, c);
            ady[v].push_back(vw);
            //ady[w].push_back(wv);
            capacidades[v][w] = c;
        }
        cout << solve(maxPeso) << endl;
        t--;
    }
    return 0;
}


