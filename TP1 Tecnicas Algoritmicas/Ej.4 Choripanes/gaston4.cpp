#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.failbit);
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
/* F indica el minimo costo de poner k proveedurias a partir del puesto i
 * 
 *          ┌ 
 * 			| costeAcum             si k=0
 * 			| 
 * f(i,k) = ┤ 
 * 			|
 * 			|
 * 			└ 
 * 
 * 
 * 
 * 
 * 
 */
int f(int provAnt, int costeAcum, int i, int k, vector<int>& v){
    //if(dp[costeAcum][i][k] != -1) return dp[costeAcum][i][k];
    if(k == 0){
        //Actualizo los gastos de los puestos restantes desde la proveeduria anterior hasta el ultimo puesto
        forr(p, provAnt, N)
            costeAcum += abs(puestos[provAnt] - puestos[p]);
        return costeAcum;//costo(v);
    }
    int costo = INF; int puestoMin = INF;
    forr(j, i, N-k+1){
        v.push_back(puestos[j]);
		//Actualizo los gastos de los puestos desde el puesto siguiente inmediato a
		//la proveeduria anterior hasta el puesto (j-1)-esimo inclusive
		int ct = costeAcum;
		forr(p, provAnt+1, j){
			if(provAnt != -1){//si provAnt es -1, entonces no hay proveeduria anterior
				int costoAProvAnt = abs(puestos[provAnt] - puestos[p]);
				int costoAProvSig = abs(puestos[j] - puestos[p]);
				if(costoAProvSig < costoAProvAnt)
					ct += costoAProvSig;
                else
                    ct += costoAProvAnt;
			}else{
				ct += abs(puestos[j] - puestos[p]);
			}

		}
        int costoI = f(j, ct, j+1, k-1, v);
        if(costoI < costo){
            costo = costoI;
            puestoMin = puestos[j];
        }
        v.pop_back();
    }
    RES[K-k] = puestoMin;
    //dp[costeAcum][i][k] = costo;
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
        cout << f(-1,0,0,K,v) << "\n";
        forn(i,RES.size()) {
            cout << RES[i];
            if(i != RES.size()-1) cout << " ";
        }
        cout << "\n";
        forn(i,N+2) forn(j,N+1) forn(k,K+1)dp[i][j][k] = -1;

    }
    return 0;
}
