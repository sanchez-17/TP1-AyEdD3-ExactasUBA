#include <iostream>
#include <vector>
#include <functional>

using namespace std;

int N, K;
vector<int> puestos;
int INF = 1e9;
vector<vector<vector<int>>> memo;

int costo(int u, int x){
    int sum = 0;
    for(int i = x; i < u; i++){
        sum = sum + min(abs(puestos[i] - puestos[x]), abs(puestos[i] - puestos[u]));
    }
    return sum;
}

int distFinal(int u, int x){
    int sum = 0;
    for(int i = x; i < u; i++){
        sum = sum + abs(puestos[i] - puestos[u]);
    }
    return sum;
}

int costoPrimero(int i){
    int sum = 0;
    for(int j = i; j < N; j++){
        sum = sum + abs(puestos[j] - puestos[i]);
    }
    return sum;
}

//u = ultima proveeduria puesta
//i = cant de puestos, o posicion donde se planea poner la sig proveeduria
//k = cant de proveedurias
//prov = vector de posiciones de las proveedurias
int choripanes(int u, int i, int k, vector<int>& prov){
    if(i==-1 && k!= 0) return INF;
    if(k==0) return distFinal(u,0);
    if(memo[u][i][k] != -1) return memo[u][i][k];

    int coloco = choripanes(i,i-1,k-1,prov);
    int no_coloco = choripanes(u, i-1, k, prov);

    if(u == N){
        coloco = coloco + costoPrimero(i);
    }else{
        coloco = coloco + costo(u,i);
    }

    if(coloco < no_coloco){
        memo[u][i][k] = coloco;
        return coloco;
    }else{
        memo[u][i][k] = no_coloco;
        return no_coloco;
    }
}

vector<int> reconstruccion(int u, int i, int k){
    vector<int> res;
    for(int j = i-1; j>=0; j--){
        if(memo[u][j][k] != memo[u][j+1][k]){
            res.push_back(puestos[j+1]);
            u = j+1;
            k = k-1;
        }
    }
    if(k>0){
        res.push_back(puestos[0]);
    }
    return res;
}

void solve(){
    vector<int> proveedurias;
    cout << choripanes(N,N-1, K, proveedurias) << endl;
    vector<int> res = reconstruccion(N, N-1, K);
    for(int i = res.size()-1; i > 0; i--){
        cout<<res[i]<<" ";
    }
    cout<<res[0]<<endl;
}

int main(){
    int c;
    cin >> c;
    for(int i = 0; i < c; i++){
        cin >> N >> K;
        puestos = vector<int>(N, -1);
        memo = vector<vector<vector<int>>>(N + 1, vector<vector<int>>(N + 1, vector<int>(K+1, -1)));
        for(int j = 0; j < N; j++){
            cin >> puestos[j];
        }
        solve();
    }
    return 0;
}