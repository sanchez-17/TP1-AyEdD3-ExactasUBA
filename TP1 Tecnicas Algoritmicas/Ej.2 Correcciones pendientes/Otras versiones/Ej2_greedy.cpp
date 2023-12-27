#include <iostream>
#include <algorithm>
#include "../utilities.h"
#define ll unsigned long long
#define pll pair<ll,ll>
using namespace std;
int N;
vector<vector<ll>> M;
vector<ll> factor;
vector<ll> tiempo;
vector<pll> parciales;
ll MOD = 1e9 + 7;

bool porCociente (pll i,pll j) { return  (i.fst * j.snd) < (j.fst * i.snd) ; }

void solve(){
    ll res = 0;
    ll tiempo = 0;
    forn(i,N) {
        tiempo +=  parciales[i].fst;
        res += parciales[i].snd * tiempo ;
    }
    cout<<res % MOD<<"\n";
}

int main(){
    int m;cin>>m;
    forn(i,m) {
        cin >> N;
        tiempo.rz(N);factor.rz(N);parciales.rz(N);
        forn(i,N) cin >> tiempo[i];
        forn(i,N) cin >> factor[i];
        forn(i,N) parciales[i] = {tiempo[i],factor[i]} ;
        sort(parciales.begin(),parciales.end(),porCociente);
        //impVectorTuplas(parciales);
        solve();
    }
    return 0;
}
