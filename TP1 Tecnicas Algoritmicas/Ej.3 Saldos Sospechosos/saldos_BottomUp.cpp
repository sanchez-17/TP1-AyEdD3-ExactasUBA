#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.failbit);
#define forr(i,a,b) for(int i = (int) a; i < (int) b; i++)
#define forn(i,n) forr(i,0,n)
#define rz resize
#define sz(x) (int)(x).size()

#define pb push_back
#define ppb pop_back

int m, N, W, MAX_SUM;
string RES;
const int MAX_W = 1000, MAX_N = 100;
int libro[100];
bool dp[MAX_N][MAX_N * MAX_W][2] = {{{false}}};

void f(int i, int sum, string& res ){
	forr(i,0,N+1)
	forn(sum, MAX_SUM + 1){
		bool & ret = dp[i + MAX_N][sum + MAX_SUM] = dp[i + MAX_N -1][ sum - libro[i] + MAX_SUM];
		if(ret)
			ret |= dp[i-1][sum -libro[i]];
	}
}


int main(){
	fastio;
    cin>>m;
    forn(c,m){
        cin >> N >> W; W = W/100;
        forn(i, N) {int x; cin >> x; libro[i] = x/100;}
        //Vemos el rango
        MAX_SUM = 0 ;
        forn(i, N) MAX_SUM += libro[i];
        //Computamos respuesta
        string res;
        f(0, 0, res);
        cout<< RES << endl;
        //Reiniciamos la str de memoizacion
        forn(i,N) forn(j, 2*MAX_SUM+2){
			memo[i][j][0] = false;
			memo[i][j][1] = false;
		};
		RES = "";
    }
	return 0;
}

