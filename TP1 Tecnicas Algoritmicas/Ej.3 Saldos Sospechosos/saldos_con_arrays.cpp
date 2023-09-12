#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.failbit);
#define forr(i,a,b) for(int i = (int) a; i < (int) b; i++)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i = (int) b-1; i >= (int) a; i--)
#define dforn(i,n) dforr(i,0,n)
#define rz resize
#define sz(x) (int)(x).size()

#define pb push_back
#define ppb pop_back


int m, N, W, sumaMax;
string RES;
const int MAX_W = 1000, MAX_N = 100;
int libro[100];
bool memo[MAX_N][MAX_N * MAX_W][2] = {{{false}}};
vector<int> acum;

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
        bool a = false;
        if(sum - libro[i] - acum[i+1] <= W) a = f(i+1, sum-libro[i], res);
        res.ppb();
	//Pruebo sumando
        res.pb('+');
        bool b = false;
        if( sum + libro[i] + acum[i+1] >= W) b = f(i+1, sum+libro[i], res);
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
    forn(c,m){
        cin >> N >> W; W = W/100;
        forn(i,N) {int x; cin >> x; libro[i] = x/100;}
        //Vemos el rango de valores que toma sum en f y la suma acumulada 
        //de las entradas del libro 
        acum.rz(N+1,0);
        dforn(i,N) acum[i] = acum[i+1] + libro[i];
        sumaMax = 0 ;
        forn(i,N) sumaMax += libro[i];
        //Computamos respuesta
        string res;
        f(0, 0, res);
        cout<< RES << endl;
        //Reiniciamos la str de memoizacion
        forn(i,N) forn(j,2*sumaMax+2){
			memo[i][j][0] = false;
			memo[i][j][1] = false;
		};
		RES = "";acum.clear();
    }
	return 0;
}

