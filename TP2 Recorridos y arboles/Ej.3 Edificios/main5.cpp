#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int N, M, D, R, Dmax, Rmax;
const int INF = 1e9, Dcota = 1e6;

//Quiero el C = D/R que cumpla
// Sum(d_i)/ Sum(r_i) >= C
// Desarrollando queda
// 0 >= Sum(C . r_i - d_i) = f, y f considero el peso de AGM de G' donde e en E' tienen peso w(e) = C . r_i - d_i

struct Arista{
    Arista(int _u, int _v, int _d, int _r){
        u = _u; v = _v; d = _d; r = _r;
    }
    long double w;
    int u, v, d, r;

    bool operator<(const Arista& e) const
    {
        return w < e.w;
    }
};

vector<Arista> aristas;

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
    D = R = 0;
    sort(aristas.begin(),aristas.end()); // Ordena segun el 1er elem, en este caso el peso
    DSU dsu(n);

    int contAristas = 0;
    for(auto e : aristas){ // e = [w,u,v,r,d], w = c*r-d
        long double w = e.w;
        int u = e.u, v = e.v, r = e.r, d = e.d;

        //u y v estan en distinta cc
        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u, v); // Agrega arista u-v
            res += w; // Suma el peso de u-v
            contAristas++;
            D += d;
            R += r;
        }
        if(contAristas == n-1) break;
    }

    if(contAristas == n-1) return res;
    else return INF; // Cuando no logro conectarlos, pero en nuestro caso siempre va a poder
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
        long double suma = kruskal(N);
        if(suma <= 0){
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
    cout << Dmax << " " << Rmax << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.failbit);
    int C;
    cin >> C;
    for(int c = 0; c < C; c++){
        cin >> N >> M;
        aristas.clear();
        for(int m = 0; m < M; m++){
            int u, v, d, r;
            cin >> u >> v >> d >> r;
            u--; v--; //Indexo los vertices comenzando desde 0
            Arista e(u, v ,d, r);
            aristas.push_back(e);
        }
        Dmax = 0;
        Rmax = 0;
        solve();
    }
    return 0;
}
