#include <iostream>
#include <vector>
#include <math.h>
#include "../../utilities.h"

int m, N, W, RANGO; vector<int> libro;vector<char> RES; int sumaMax, sumaMin;
vector<vector<int>> memo ;
bool f(int i,int sum){
    if(i == 0) return sum == 0;
    else{
        if(memo[i][sum + RANGO] != -1) return memo[i][sum + RANGO];
        bool a = f(i-1, sum-libro[i]);
        bool b = f(i-1, sum+libro[i]);
        if( a && b ) RES.pb('?');
        else if( a ) RES.pb('-');
        else RES.pb('+');
        return a || b;
    }
    
}

int main(){
    cin>>m;
    forn(i,m){
        cin>>N>>W;libro.rz(N);//Acum.rz(N+1,0);
        forn(i,N) cin >> libro[i] / 100;
        //Vemos el rango
        sumaMax = 0 ;
        forn(i,N) sumaMax += libro[i];
        RANGO = 2*sumaMax+1; memo.rz(N+1,vector<int>(RANGO,-1));
        //dfor(i,N-1) Acum[i] = libro[i] + Acum[i+1];
        f(N-1,W);
        DBG(RES);
    }
	return 0;
}
