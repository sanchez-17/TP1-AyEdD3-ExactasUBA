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
int dp[MAX_N][MAX_K] = {{-1}};
vector<int> RES;

int costo(vector<int>& v){
    int costo = 0;
    forn(i,N){
        int distMin = INF;
        forn(j,K) distMin = min(distMin, abs(puestos[i]-v[j]));
        costo += distMin;
    }
    return costo;
}

int f(int i, int k, vector<int>& v){
    if(k > N-i)       return INF;
    //if(dp[i][k]!= -1) return dp[i][k];
    if(k == 0){
        int res = costo(v);
        if(res < MIN_COSTO ) {MIN_COSTO = res; RES = v;}
        return res;
    }
    int costo = INF;
    forr(j,i,N-k+1){
        v.push_back(puestos[j]);
        int costoI = f(j+1,k-1,v);
        costo = min(costo, costoI);
        v.pop_back();
    }
    //dp[i][k] = costo;
    return costo;
}

int main(){
    cin >> c;
    forn(t,c){
        cin >> N >> K;
        forn(i,N) cin >> puestos[i];
        vector<int> v;
        cout << f(0,K,v) << "\n";
        forn(i,RES.size()) {
            cout << RES[i];
            if(i != RES.size()-1) cout << " ";
        }
        cout << "\n";
        forn(i,N+1) forn(j,K+1) dp[i][j] = -1;

        RES = {};
    }
    return 0;
}
