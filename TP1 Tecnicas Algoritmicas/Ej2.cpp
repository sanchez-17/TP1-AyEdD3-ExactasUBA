#include <iostream>
#include "../backtracking/utilities.h"
#define ll unsigned long long
using namespace std;
int N;vector<vector<ll>> M;ll MOD = 1e9 + 7;
ll SUM_MIN=1e10;

void f(vector<bool>& usados,ll descGral,ll tiempo,int cnt){
    if(cnt==N) SUM_MIN = descGral < SUM_MIN ? descGral : SUM_MIN;
    else{
        forn(i,N) if(!usados[i]){
            usados[i] = true;
            ll tiempoActual =  tiempo+M[0][i];
            f(usados, descGral +  tiempoActual * M[1][i],tiempoActual, cnt+1);
            usados[i] = false;
        }
    }
}

void solve(){
    vector<bool> usados(N,false);
    f(usados,0,0,0);
    cout<<SUM_MIN % MOD<<"\n";
}

int main(){
    int m;cin>>m;
    forn(i,m) {
        cin >> N; M.clear(); M.rz(2,vector<ll>(N));
        forn(j,2) forn(k,N) cin >> M[j][k];
        impMatriz(M);
        solve();
        SUM_MIN = 1e10;
    }

    return 0;
}
