#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.failbit);
#define forr(i,a,b) for(int i = (int) a; i < (int) b; i++)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i = (int) b-1; i >= (int) a; i--)
#define dforn(i,n) dforr(i,0,n)
#define fst first
#define snd second

int m, N, W, sumaMax;
string RES;
const int MAX_W = 1000, MAX_N = 100;
int libro[100];
vector<vector<pair<bool,char> > > dp;
//bool memo[MAX_N][MAX_N * MAX_W][2] = {{{false}}};
vector<int> acum;

bool f(int i, int sum){
    if(i == N) return sum == W;
    else{
        if(dp[i][sum + sumaMax].fst) return dp[i][sum + sumaMax].snd != 'n' ;
        //Pruebo restando
        bool a = false;
        if(sum - libro[i] - acum[i+1] <= W) a = f(i+1, sum-libro[i]);
        //Pruebo sumando
        bool b = false;
        if( sum + libro[i] + acum[i+1] >= W) b = f(i+1, sum+libro[i]);

        char r;
        if(a && b) r = '?';
        else if(a) r = '-';
        else if(b) r = '+';
        else r = 'n';
        dp[i][sum + sumaMax].fst = true;
        dp[i][sum + sumaMax].snd = r;
        return a || b;
    }

}

int main(){
    fastio;
    cin>>m;
    forn(c,m) {
        cin >> N >> W;
        W = W / 100;
        forn(i, N) {
            int x;
            cin >> x;
            libro[i] = x / 100;
        }
        //Vemos el rango de valores que toma sum en f y la suma acumulada
        //de las entradas del libro
        acum = vector<int>(N + 1, 0);
        dforn(i, N) acum[i] = acum[i + 1] + libro[i];
        sumaMax = 0;
        forn(i, N) sumaMax += libro[i];
        dp = vector<vector<pair<bool,char> > >(N, vector<pair<bool, char>>(2 * sumaMax + 2, pair<bool, char>(make_pair(false, 'n'))));
        //Computamos respuesta
        f(0, 0);
        forn(i, N) forn(j, 2 * sumaMax + 2){
            if (dp[i][j].fst) cout << dp[i][j].snd;
        }
        if(c != m-1)cout << "\n";
    }

    return 0;
}

