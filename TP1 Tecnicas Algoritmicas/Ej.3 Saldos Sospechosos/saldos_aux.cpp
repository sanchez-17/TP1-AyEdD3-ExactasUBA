#include "../../utilities.h"

int m, N, W, RANGO, sumaMax;
string RES;
vector<int> libro;
vector<vector<int>> memo ;

void calcularRes(string& res){
	DBS("Tengo 2 soluciones: \n");
	DBG2(RES,res);
	forn(i, sz(res)) if(res[i] != RES[i]) RES[i] = '?';
}

bool f(int i, int sum, string& res ){
	DBG4(i,sum,res,RES);//impAux(memo);
    if(i == N) if (sum == W) {
					//Llegue a una solucion valida y debo saber si habia una antes
					if(sz(RES) == 0) RES = res;
					else             calcularRes(res);
					return true;
				}else   return false;
    else{
        if(memo[i][sum + sumaMax + 1] != -1) return memo[i][sum + sumaMax];
        bool r;
	//Pruebo restando
		//res.insert(0, 1, '+');
        res.pb('-');
        bool a = f(i+1, sum-libro[i], res);
        res.ppb();
	//Pruebo sumando
        //res.insert(0, 1, '-');
        res.pb('+');
        bool b = f(i+1, sum+libro[i], res);
        res.ppb();
        //res.erase(0, 1);
	
		r =  a || b;
        memo[i][sum + sumaMax] = r; //-1 indef, 1 true, 0 false
        return r;
    }
    
}

int main(){
    cin>>m;
    forn(i,m){
		RAYA; DBG2("Test",i);
        cin >> N >> W; W = W/100; libro.rz(N);
        forn(i,N) {int x; cin >> x; libro[i] = x/100;}
        //Vemos el rango
        sumaMax = 0 ;
        forn(i,N) sumaMax += libro[i];
        RANGO = 2*sumaMax+1;
        memo.rz(N,vector<int>(RANGO,-1));
        DBG2("libro",libro);DBG3("sum",W,sumaMax);
		string res;
		
		RAYA;RAYA;
        f(0, 0, res);
        DBG(RES);
        memo.clear(); libro.clear();RES.clear();
		RAYA;RAYA;
    }
	return 0;
}

