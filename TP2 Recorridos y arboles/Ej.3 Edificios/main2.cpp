#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int N, M, contador, D, R, Dmax, Rmax;
const int INF = 1e7;
vector<tuple<long double,int,int>> aristasKruskal;

// Para saber el peso de las aristas en O(1)
vector<vector<vector<int>> > peso;

struct Arista{
    Arista(int uu, int vv, int dist, int rep){ u = uu; v = vv; d = dist; r = rep; }
    int u, v, d, r;
};

vector<Arista> Rutas; // Aristas originales

struct DSU {
    DSU(int n){
        padre = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
        tamano = vector<int>(n,1);
    }

    int find(int v){
        while(padre[v] != v) v = padre[v];
        return v;
    }

    void unite(int u, int v){
        u = find(u); v = find(v);
        if(tamano[u] < tamano[v]) swap(u,v);
        //ahora u es al menos tan grande como v
        padre[v] = u;
        tamano[u] += tamano[v];
    }

    vector<int> padre;
    vector<int> tamano;

    //tamano[v] <= n
    //INV: si padre[v] != v entonces tamano[padre[v]] >= 2*tamano[v]
};

long double kruskal(vector<tuple<long double,int,int>>& E, int n){
    long double res = 0;
    D = 0;
    R = 0;
    sort(E.rbegin(),E.rend()); // Ordena segun el 1er elem, en este caso el peso
    DSU dsu(n);

    int aristas = 0;
    for(auto e : E){ // e  = [w,u,v]
        //u y v estan en distinta cc
        if(dsu.find(get<1>(e)) != dsu.find(get<2>(e))){
            dsu.unite(get<1>(e), get<2>(e)); // Agrega arista u-v
            res += get<0>(e); // Suma el peso de u-v
            aristas++;
            D += peso[get<1>(e)][get<2>(e)][0];
            R += peso[get<1>(e)][get<2>(e)][1];
        }
        if(aristas == n-1) break;
    }

    if(aristas == n-1) return res;
    else return INF; // Cuando no logro conectarlos, pero en nuestro caso siempre va a poder
}

// para cada c
// vamos guardando/actualizando las aristas con el nuevo "peso"
// las ordenamos
// correr kruskal
// kruskal devuelve la suma de esas aristas
// si la suma queda por debajo de 0, guardo esta Cmax y busco otra mejor (por arriba)
// si la suma queda mayor a 0, no guardo este c y busco otro (por debajo)
// queremos contar cuantas "iteraciones" (busquedas binarias?) hace.
// si ya hizo, por ejemplo, 20-40, parar y devolvemos la D y R correspondientes al ultimo Cmax encontrado

void busqueda_binaria(long double a, long double b){
    while(contador < 40){
        contador++;
        long double mid = ((a+b)/2);
        //con las aristas creamos nuevas para el kruskal (usa vector tripla)
        aristasKruskal.clear(); //borro las que ya estaban
        for(Arista ruta : Rutas){
            aristasKruskal.push_back({mid*ruta.r - ruta.d, ruta.u, ruta.v}); //nuevo peso, vertice u, vertice v
        }
        long double suma = kruskal(aristasKruskal, N);
        if(suma <= 0){ // <= 0 ?
            a = mid;
            //Cmax = mid;
            //actualizar D y R
            Dmax = D;
            Rmax = R;
        }else{ //cuando es mayor, quiero uno mas chico
            b=mid;
        }
    }
}

void solve(){
    busqueda_binaria(0, 1e11);
    cout<<Dmax<<" "<<Rmax<<endl;
}

int main() {
    int C;
    cin >> C;
    for(int c = 0; c < C; c++){
        cin >> N >> M;
        Rutas.clear();
        peso = vector<vector<vector<int>> >(N, vector<vector<int>>(N, vector<int>(2,-1)));
        for(int m = 0; m < M; m++){
            int u, v, d, r;
            cin >> u >> v >> d >> r;
            u--;
            v--;
            peso[u][v][0] = d;
            peso[v][u][0] = d;
            peso[u][v][1] = r;
            peso[v][u][1] = r;
            Arista nueva(u, v ,d, r);
            Rutas.push_back(nueva);
        }
        contador = 0;
        Dmax = 0;
        Rmax = 0;
        solve();
    }
    return 0;
}

