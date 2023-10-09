#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int N, M, contador, D, R, Dmax, Rmax;
const int INF = 1e7;
vector<tuple<long double,int,int, int, int> > aristasKruskal;
int Dcota;

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
};

long double kruskal(vector<tuple<long double,int,int>>& E, int n){
    long double res = 0;
    D = 0;
    R = 0;
    sort(E.begin(),E.end()); // Ordena segun el 1er elem, en este caso el peso
    DSU dsu(n);

    int aristas = 0;
    for(auto e : E){ // e  = [w,u,v,r,d]
        //u y v estan en distinta cc
        if(dsu.find(get<1>(e)) != dsu.find(get<2>(e))){
            dsu.unite(get<1>(e), get<2>(e)); // Agrega arista u-v
            res += get<0>(e); // Suma el peso de u-v
            aristas++;
            D += get<4>(e);
            R += get<3>(e);
        }
        if(aristas == n-1) break;
    }

    if(aristas == n-1) return res;
    else return INF; // Cuando no logro conectarlos, pero en nuestro caso siempre va a poder
}

void busqueda_binaria(long double a, long double b){
    while(contador < 70){
        // para salvar casos como el de la diapo
        contador++;
        long double mid = ((a+b)/2);
        //con las aristas creamos nuevas para el kruskal (usa vector tripla)
        aristasKruskal.clear(); //borro las que ya estaban
        for(Arista ruta : Rutas){
            aristasKruskal.push_back({mid*ruta.r - ruta.d, ruta.u, ruta.v, ruta.r, ruta.d}); //nuevo peso, vertice u, vertice v
        }
        long double suma = kruskal(aristasKruskal, N);
        if(suma <= 0){ // <= 0 ?
            a = mid;
            Dmax = D;
            Rmax = R;
        }else{ //cuando es mayor, quiero uno mas chico
            b=mid;
        }
    }
}

void solve(){
    busqueda_binaria(0, Dcota);
    cout<<Dmax<<" "<<Rmax<<endl;
}

int main() {
    int C;
    cin >> C;
    for(int c = 0; c < C; c++){
        cin >> N >> M;
        Rutas.clear();
        Dcota = 0;
        for(int m = 0; m < M; m++){
            int u, v, d, r;
            cin >> u >> v >> d >> r;
            u--;
            v--;
            Dcota += d;
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
