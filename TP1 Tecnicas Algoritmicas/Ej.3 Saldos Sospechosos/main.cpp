#include <iostream>
#include <vector>
using namespace std;
#define forr(i,a,b) for(int i = (int) a; i < (int) b; i++)
#define forn(i,n) forr(i,0,n)
#define INDEF 'a' //Valor que representa indefinido en char

int N, W, sumaMax, RANGO;
int libro[100];
vector<vector<int>> dp;
char RES[100];

bool f(int i, int sum){
    if(i == N)                          return sum == W;
    if(dp[i][sumaMax + sum] != -1)    return dp[i][sumaMax + sum];

    bool a = f(i+1,sum - libro[i]);
    bool b = f(i+1,sum + libro[i]);

    if(a && b) RES[i] = '?';
    else if (a){
        //Anteriormente se pudo con sumar el i-esimo elemento
        if(RES[i] == '+')        RES[i] = '?';
        else if(RES[i] == INDEF) RES[i] = '-';
    }else if (b){
        //Anteriormente se pudo con restar el i-esimo elemento
        if(RES[i] == '-')        RES[i] = '?';
        else if(RES[i] == INDEF) RES[i] = '+';
    }
    dp[i][sumaMax + sum] = a || b;
    return a || b;
}

int main(){
    int m;
    cin>>m;
    forn(c,m){
        cin >> N >> W; W = W/100;
        //Generamos el libro de entradas
        forn(i,N) {int x;cin >> x;libro[i] = x/100;}
        //Vemos el rango maximo del valor de la suma para las entradas del libro
        sumaMax = 0 ;
        forn(i,N) {sumaMax += libro[i];}
        RANGO = 2*sumaMax + 1;
        //Reiniciamos dp y la respuesta
        dp = vector<vector<int>>(N,vector<int>(RANGO,-1));
        forn(r,N) RES[r] = INDEF;
        //Computamos respuesta
        f(0,0);
        //Imprimimos respuesta
        forn(r,N) cout << RES[r];
        cout<<'\n';
    }
    return 0;
}
