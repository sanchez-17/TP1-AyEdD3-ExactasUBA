#include <vector>
#include <algorithm>
#include <tuple>
#include <iostream>
using namespace std;

int N, M, contador, D, R, Dmax, Rmax;
const int INF = 1e7, Dcota = 1e6;;

vector<tuple<long double,int,int, int, int> > aristasKruskal; //c*r-d, u, v, d, r

struct Arista{
    Arista(int uu, int vv, int dist, int rep){
        u = uu; v = vv; d = dist; r = rep;
    }
    int u, v, d, r;
};

//struct AristaKruskal{int cd_r, u, v, d, r;};

vector<Arista> Rutas; // Aristas originales

//Estructura de UFDS
struct DSU {
    DSU(int n){
        padre = vector<int>(n);
        for(int v = 0; v < n; v++) padre[v] = v;
        tamano = vector<int>(n,1);
    }
    int find(int v){
        if( v == padre[v] ) return v;
        else return padre[v] = find(padre[v]);
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

long double kruskal( int n){
    long double res = 0;
    D = 0;
    R = 0;
    sort(aristasKruskal.begin(),aristasKruskal.end()); // Ordena segun el 1er elem, en este caso el peso
    DSU dsu(n);

    int aristas = 0;
    for(auto arista : aristasKruskal){ // e  = [w,u,v,r,d], w = c*r-d
        long double w = get<0>(arista);
        int u = get<1>(arista),
                v = get<2>(arista),
                r = get<3>(arista),
                d = get<4>(arista);

        //u y v estan en distinta cc
        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u, v); // Agrega arista u-v
            res += w; // Suma el peso de u-v
            aristas++;
            D += d;
            R += r;
        }
        if(aristas == n-1) break;
    }

    if(aristas == n-1) return res;
    else return INF; // Cuando no logro conectarlos, pero en nuestro caso siempre va a poder
}

void busqueda_binaria(long double a, long double b){
    long double sumaActual = -INF;
    while(contador < 50 ){
        // para salvar casos como el de la diapo
        contador++;
        long double mid =(a+b)/2;
        //con las aristas creamos nuevas para el kruskal (usa vector tripla)
        aristasKruskal.clear(); //borro las que ya estaban
        for (Arista ruta: Rutas)
            aristasKruskal.push_back(
                    {mid * ruta.r - ruta.d, ruta.u, ruta.v, ruta.r, ruta.d}); //nuevo peso, vertice u, vertice v
        long double suma = kruskal(N);
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
    ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.failbit);
    int C;
    cin >> C;
    for(int c = 0; c < C; c++){
        cin >> N >> M;
        Rutas.clear();
        for(int m = 0; m < M; m++){
            int u, v, d, r;
            cin >> u >> v >> d >> r;
            u--;
            v--;
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
