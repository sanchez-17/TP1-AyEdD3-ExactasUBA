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


/* ? : 0
 * + : 1
 * - : 2
 */
int m, N, W, sumaMax;
const int MAX_W = 1000, MAX_N = 100;
int libro[100];
vector<vector<int > > dp;
//bool memo[MAX_N][MAX_N * MAX_W][2] = {{{false}}};
vector<int> acum;

bool f(int i, int sum){
    if(i == N) return sum == W;
    else{
        if(dp[i][sum + sumaMax] != -1) return dp[i][sum + sumaMax];
        //Pruebo restando
        bool a = false;
        if(sum - libro[i] - acum[i+1] <= W) a = f(i+1, sum-libro[i]);
        //Pruebo sumando
        bool b = false;
        if( sum + libro[i] + acum[i+1] >= W) b = f(i+1, sum+libro[i]);

        int r;
        if(a && b) r = 0; //?
        else if(a) r = 2; //-
        else if(b) r = 1; //+
        else r = -1;
        dp[i][sum + sumaMax] = r;
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
        dp = vector<vector<int > >(N, vector<int>(2 * sumaMax + 2, -1));
        //Computamos respuesta
        f(0, 0);
        forn(i, N) forn(j, 2 * sumaMax + 2){
                if (dp[i][j] != -1) {
                    int res = dp[i][j];
                    if (res == 0) cout << '?';
                    else if (res == 1) cout << '+';
                    else if (res == 2) cout << '-';
                }
            }
        if(c != m-1)cout << "\n";
    }

    return 0;
}
