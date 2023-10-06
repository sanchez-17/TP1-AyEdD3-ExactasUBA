#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#define dd double double
using namespace std;
int N, M;
int contador;
vector<tuple<int,int,int>> aristasKruskal;
vector<Aristas> aristas;
int D, R, Cmax;

//struct aristas

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

void kruskal(vector<tuple<int,int,int>>& E, int n){
    long long res = 0;
    sort(E.begin(),E.end());
    DSU dsu(n);

    int aristas = 0;
    for(auto [w,u,v] : E){
        //u y v estan en distinta cc?
        if(dsu.find(u) != dsu.find(v)){
            dsu.unite(u,v);
            res += w;
            aristas++;
        }
        if(aristas == n-1) break;
    }

    if(aristas == n-1) cout<<res<<'\n';
    else cout<<"IMPOSSIBLE\n";
}

/*
int main(){
    int n,m;
    cin>>n>>m;
    vector<tuple<int,int,int>> E(m); //(costo,u,v)
    for(int i = 0; i < m; i++){
        int u,v,w;
        cin>>u>>v>>w;
        u--, v--;
        E[i] = {w,u,v};
    }

    kruskal(E,n);

    return 0;
}

*/
// para cada c
// vamos guardando/actualizando las aristas con el nuevo "peso"
// las ordenamos
// correr kruskal
// kruskal devuelve la suma de esas aristas
// si la suma queda por debajo de 0, guardo esta Cmax y busco otra mejor (por arriba)
// si la suma queda mayor a 0, no guardo este c y busco otro (por debajo)
// queremos contar cuantas "iteraciones" (busquedas binarias?) hace.
// si ya hizo, por ejemplo, 20-40, parar y devolvemos la D y R correspondientes al ultimo Cmax encontrado

void busqueda_binaria(dd a, dd b){
    while(b-a>1 && contador < 40){
        contador++;
        dd mid = ((a+b)/2);
        //con las aristas creamos nuevas para el kruskal (usa vector tripla)
        aristasKruskal.clear(); //borro las que ya estaban
        for(Arista a : aristas){
            aristasKruskal.push_back({a.u, a.v, mid*a.r - a.d}); //vertice u, vertice v, nuevo peso
        }
        if(kruskal(aristasKruskal) < 0){
            a = mid;
            Cmax = mid; //el mejor c hasta ahora
            //actualizar D y R
            // D = 
            // R =
        }else{
            b=mid;
        }
    }
}

void solve(){
    busqueda_binaria(0, 1e11);
    cout<<D<<" "<<R<<endl;
}

int main() {
    int C;
    cin >> C;
    for(int c = 0; c < C; c++){
        cin >> N >> M;
        for(int m = 0; m < M; m++){
            int u, v, d, r;
            cin >> u >> v >> d >> r;
        }
        contador = 0;
        aristasKruskal.clear(); //las aristas para el kruskal con la suma
        solve();
    }
    return 0;
}
