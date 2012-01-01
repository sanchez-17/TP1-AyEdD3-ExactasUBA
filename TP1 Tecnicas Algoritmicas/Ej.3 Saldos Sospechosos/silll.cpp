#include <iostream>
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define forr(i,a,b) for(int i = (int) a; i < (int) b; i++)
#define forn(i,n) forr(i,0,n)

int N;
int W;
vector<int> libro;
vector<vector<int>> memo;
vector<char> RES;
int sumaMax;
int RANGO;

bool f(int i, int sum){
    if(i == N){
        return sum == W;
    }
    if(memo[i][sumaMax + sum] != -1){
        return memo[i][sumaMax + sum];
    }

    bool a = f(i+1,sum - libro[i]);
    bool b = f(i+1,sum + libro[i]);

    if(a && b){
        RES[i] = '?';
    } else if (a){
        //se pudo con suma
        if(RES[i] == '+'){
            RES[i] = '?';
        } else if(RES[i] == 'a'){
            RES[i] = '-';
        }
    } else if (b){
        //se pudo con resta
        if(RES[i] == '-'){
            RES[i] = '?';
        } else if(RES[i] == 'a'){
            RES[i] = '+';
        }
    }
    memo[i][sumaMax + sum] = a || b;
    return a || b;
}

int main(){
    int m;
    cin>>m;
    forn(i,m){
        cin >> N >> W; W = W/100;
        libro = vector<int>(N,0);
        forn(i,N) {int x;cin >> x;libro[i] = x/100;}
        //Vemos el rango
        sumaMax = 0 ;
        forn(i,N) {sumaMax += libro[i];}
        RANGO = 2*sumaMax + 1;
        memo = vector<vector<int>>(N,vector<int>(RANGO,-1));
        RES = vector<char>(N,'a');
        //DBG(memo);
        f(0,0);
        forn(i, N) {cout<<RES[i];}
    }
    return 0;
}