#include <iostream>
#include <vector>

using namespace std;

int N, K, INF = 1e9;
vector<int> puestos;
vector<vector<vector<int>>> memo;

int costo(int i, int u){
    int sum = 0;

    if(u == N){//Si es la primera vez que colocamos una proveeduria
        for(int idx = i; idx < N; idx++)
            sum += abs(puestos[idx] - puestos[i]);
        return sum;
    }

    if(i == -1){//Si es la ultima vez que colocamos una proveeduria
        for(int idx = 0; idx < u; idx++)
            sum += abs(puestos[idx] - puestos[u]);
        return sum;
    };

    for(int idx = i; idx < u; idx++)
            sum += min(abs(puestos[idx] - puestos[i]), abs(puestos[idx] - puestos[u]));
    return sum;
    }
/*
 * f(u,i,k) = min(f(i,i-1,k-1) + costo(i,u), f(u,i-1,k)), itera desde N hasta 0.
 Nos dice el minimo costo de poner k proveedurias a partir de la posicion i y habiendo colocado la ultima proveeduria en u
 Basicamente, toma el minimo entre poner una proveeduria en i y no ponerla.
 Casos base:
      * Al intentar poner la primer proveeduria, el costo es el costo de ir desde i hasta el final(No existe proveeduria anterior).
      * Al intentar poner la ultima proveeduria, el costo es el costo de ir desde el principio hasta i(No existira proveeduria posterior)
 
 costo = costo de poner una proveeduria en i y luego ir desde i hasta u. Pues los puestos que estan
 entre i y u, ya estan cubiertos por la ultima proveeduria puesta y el costo respecto a la 
 nueva proveeduria i puede ser menor respecto a la prov. u.

* u = ultima proveeduria puesta
* i = cant de puestos, o posicion donde se planea poner la sig proveeduria
* k = cant de proveedurias
*/
int choripanes(int u, int i, int k){
    //
    if(i==-1 && k!= 0)      return INF;    //Si me quedaron proveedurias por poner.
    if(k==0)                return costo(-1, u); //Si ya no me quedan proveedurias por poner.
    if(memo[u][i][k] != -1) return memo[u][i][k];
    //Coloco una proveeduria en i y actualizamos el costo desde i hasta la ultima proveeduria puesta
    int coloco = choripanes(i,i-1,k-1);
    coloco += costo(i,u);
    int no_coloco = choripanes(u, i-1, k);

    memo[u][i][k] = min(coloco, no_coloco);
    return memo[u][i][k];
}

vector<int> reconstruccion(int u, int i, int k){
    //Devuelve la secuencia de proveedurias que se colocaron
    vector<int> res;
    for(int j = i-1; j>=0; j--){
        if(memo[u][j][k] != memo[u][j+1][k]){//si coloque la proveeduria en j, pues el costo cambio
            res.push_back(puestos[j+1]); //si coloque la proveeduria en j+1
            u = j+1;                     //actualizo ultima proveeduria puesta
            k = k-1;                     //actualizo cantidad de proveedurias que me quedan por poner
        }
    }
    //si me quedan proveedurias por poner, es porque coloque la primer proveeduria en 0
    if(k>0){
        res.push_back(puestos[0]);
    }
    return res;
}

void solve(){
    cout << choripanes(N,N-1, K) << endl;
    vector<int> res = reconstruccion(N, N-1, K);
    for(int i = (int)res.size() - 1; i > 0; i--){
        cout << res[i] << " ";
    }
    cout << res[0] <<endl;
}

int main(){
    int c;
    cin >> c;
    for(int i = 0; i < c; i++){
        cin >> N >> K;
        puestos = vector<int>(N, -1);
        memo = vector<vector<vector<int>>>
                (N + 1,vector<vector<int>>
                (N + 1, vector<int>
                (K+1, -1)));
        for(int j = 0; j < N; j++){
            cin >> puestos[j];
        }
        solve();
    }
    return 0;
}
