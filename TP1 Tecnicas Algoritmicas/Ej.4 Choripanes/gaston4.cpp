#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.fai\
lbit);
#define forr(i,a,b) for(int i = (int) a; i < (int) b; i++)
#define forn(i,n) forr(i,0,n)

int c, N, K;
const int INF = 10000000;
int MIN_COSTO = INF;
const int MAX_N = 110;
const int MAX_K = 110;
int puestos[MAX_N];
int dp[MAX_N+1][MAX_N][MAX_K] = {{-1}};
vector<int> RES;

int minimoP(vector<int>& v){
    int res = INF;
    forn(i,v.size()) if(v[i] < res) res = v[i];
    return res;
}

int costo(vector<int>& v){
    int costo = 0;
    forn(i,N){
        int distMin = INF;
        forn(j,K) distMin = min(distMin, abs(puestos[i]-v[j]));
        costo += distMin;
    }
    return costo;
}

int f(int provAnt, int costeAcum, int i, int k, vector<int>& v){
    //if(dp[ant+1][i][k] != -1) return dp[ant+1][i][k];
    if(k == 0) return costo(v);
    int costo = INF; int puestoMin = INF;
    forr(j, i, N-k+1){
        v.push_back(puestos[j]);
		//ACtualizo los gastos de los puestos desde el puesto siguiente inmediato a 
		//la proveedria anterior hasta el puesto (j-1)-esimo
		forr(p, provAnt+1, j+1){
			int costoAProAnt = abs(puestos[provAnt] - puestos[p]);
			int costoAProvSig = abs(puestos[j] - puestos[p]);
			if(costoAProvSig < costoAProvAnt) costeAcum += costoAProSig - costoAProvAnt;
		}
        int costoI = f(j, costeAcum, j+1, k-1, v);
        if(costoI < costo){
            costo = costoI;
            puestoMin = puestos[j];
        }
        v.pop_back();
    }
    RES[K-k] = puestoMin;
    //dp[ant+1][i][k] = costo;
    return costo;
}

int main(){
    cin >> c;
    forn(t,c){
        cin >> N >> K;
        forn(i,N) cin >> puestos[i];
        vector<int> v; RES = vector<int>(K,-1);
        //---------------------
        //---------------------
        cout << f(0,0,0,K,v) << "\n";
        forn(i,RES.size()) {
            cout << RES[i];
            if(i != RES.size()-1) cout << " ";
        }
        cout << "\n";
        forn(i,N+2) forn(j,N+1) forn(k,K+1)dp[i][j][k] = -1;

    }
    return 0;
}
