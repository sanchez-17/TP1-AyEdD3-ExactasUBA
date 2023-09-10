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


int m, N, W, sumaMax;
string RES;
vector<int> libro;
vector<vector<vector<bool> > > memo ;

void calcularRes(string& res){
	forn(i, sz(res)) if(res[i] != RES[i]) RES[i] = '?';
}

bool f(int i, int sum, string& res ){
    if(i == N) if (sum == W) {
					//Llegue a una solucion valida y debo saber si habia una antes
					if(sz(RES) == 0) RES = res;
					else             calcularRes(res);
					return true;
				}else   return false;
    else{
		if(memo[i][sum + sumaMax][0]) if (!memo[i][sum + sumaMax][1]) return false;
	//Pruebo restando
        res.pb('-');
        bool a = f(i+1, sum-libro[i], res);
        res.ppb();
	//Pruebo sumando
        res.pb('+');
        bool b = f(i+1, sum+libro[i], res);
        res.ppb();
	
		bool r =  a || b;
		memo[i][sum + sumaMax][0] = true; 
        memo[i][sum + sumaMax][1] = r; 
        return r;
    }
    
}

int main(){
	fastio;
    cin>>m;
    forn(i,m){
        cin >> N >> W; W = W/100; libro.rz(N);
        forn(i,N) {int x; cin >> x; libro[i] = x/100;}
        //Vemos el rango
        sumaMax = 0 ;
        forn(i,N) sumaMax += libro[i];
        //Inicio estructura de memoizacion
        memo.rz(N+1,vector<vector<bool> >(sumaMax * 2 + 1, vector<bool>(2, false)));
		string res;
        f(0, 0, res);
        cout<< RES<<endl;
        memo.clear(); libro.clear();RES.clear();
    }
	return 0;
}

