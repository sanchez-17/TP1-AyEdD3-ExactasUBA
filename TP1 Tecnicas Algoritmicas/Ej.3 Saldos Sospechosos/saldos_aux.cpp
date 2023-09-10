#include <iostream>
#include <vector>
#include <math.h>
#include "../../utilities.h"

int m, N, W, RANGO; vector<int> libro;vector<char> RES; int sumaMax, sumaMin;
vector<vector<int>> memo ;

bool f(int i,int sum, vector<char>& res ){
    if(i == -1) if (sum == 0) {
			if(sz(RES) == 0) RES = res;
			else             calcularRes(res);
			return true;
		}else   return false;
    else{
        if(memo[i][sum + sumaMax] != -1) return memo[i][sum + sumaMax];
        bool r;
	//Pruebo sumando
        res.pb('+');
        bool a = f(i-1, sum-libro[i], res);
        res.ppb();
	//Pruebo restando
        res.pb('-');
        bool b = f(i-1, sum+libro[i], res);
        res.ppb();
	
	r =  a || b;
        memo[i][sum + sumaMax] = r; //-1 indef, 1 true : 0 false
        return r;
    }
    
}

int main(){
    cin>>m;
    forn(i,m){
        cin >> N >> W; W = W/100; libro.rz(N);//Acum.rz(N+1,0);
        forn(i,N) {int x;cin >> x;libro[i] = x/100;}
        //Vemos el rango
        sumaMax = 0 ;
        forn(i,N) sumaMax += libro[i];
        RANGO = 2*sumaMax+1; memo.rz(N,vector<int>(RANGO,-1));
        //DBG(memo);

        //dfor(i,N-1) Acum[i] = libro[i] + Acum[i+1];
        f(N-1,W);
        DBG(RES);
        memo.clear(); libro.clear();RES.clear();
    }
	return 0;
}

