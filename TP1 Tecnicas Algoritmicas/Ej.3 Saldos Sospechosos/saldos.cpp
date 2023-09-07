#include <iostream>
#include <vector>
#include <math.h>
#include "../../utilities.h"

int m, N, W, RANGO; vector<int> libro;vector<char> RES; int sumaMax, sumaMin;
vector<vector<int>> memo ;
bool f(int i,int sum){
    if(i == -1) return sum == 0;
    else{
        //DBG3(RES,i,sum);
        //cout << "aca hay un " << memo[i][sum + RANGO] << "\n";
        //DBG(memo);
        //DBG(memo[i][sum + sumaMax]);
        //DBGY(i);DBG4(sumaMax,sum,sumaMax + sum, RANGO);
        if(memo[i][sum + sumaMax] != -1) return memo[i][sum + sumaMax];
        //cout << "llegue lol";
        bool res;
        RES.pb('+');
        bool a = f(i-1, sum-libro[i]);
        RES.ppb();
        RES.pb('-');
        bool b = f(i-1, sum+libro[i]);
        RES.ppb();
        if( a && b ){ RES.pb('?'); res =true ;RES.ppb();}
        else if( a || b) {RES.pb(a ? '+' : '-'); res = true;RES.ppb();}
        else res = false;
        memo[i][sum + sumaMax] = res; //-1 indef, 1 true : 0 false
        return res;
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
