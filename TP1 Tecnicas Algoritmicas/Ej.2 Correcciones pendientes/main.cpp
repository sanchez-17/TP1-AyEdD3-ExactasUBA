#include <iostream>
#include <algorithm>
#include <vector>
#define ll unsigned long long
#define pll pair<ll,ll>
#define forr(i,a,b) for(int i=(int)a;i<(int)b;i++)
#define forn(i,n) forr(i,0,n)
#define rz resize
#define fst first
#define snd second
using namespace std;
int N;
vector<ll> factor;
vector<ll> tiempo;
vector<pll> parciales;
ll MOD = 1e9 + 7;

bool porCociente (pll i,pll j) { return  (i.fst * j.snd) < (j.fst * i.snd) ; }

void solve(){
    ll res = 0;
    ll tiempo = 0;
    forn(i,N) {tiempo +=  parciales[i].fst; res += parciales[i].snd * tiempo;};
    cout<<res % MOD<<"\n";
}

int main(){
	//Magia negra para ganar tiempo
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    int m;cin>>m;
    forn(i,m) {
        cin >> N;
        tiempo.rz(N);factor.rz(N);parciales.rz(N);
        forn(i,N) cin >> tiempo[i];
        forn(i,N) cin >> factor[i];
        forn(i,N) parciales[i] = make_pair(tiempo[i],factor[i]);
        sort(parciales.begin(),parciales.end(),porCociente);
        solve();
    }
    return 0;
}
