#include <iostream>
#include <algorithm>
using namespace std;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.failbit);
#define forr(i,a,b) for(int i = (int) a; i < (int) b; i++)
#define forn(i,n) forr(i,0,n)
#define rz resize
#define sz(x) (int)(x).size()

int N,M;
const int MAX_N = 120, MAX_M = 120;
char tablero[MAX_N][MAX_M];
bool camino[MAX_N][MAX_M] = {{false}};
int MAX = -1, MIN = 121;
bool posible;

/*
 *Arriba = 1
 *Abajo = 2
 *Izquierda = 3
 *Derecha = 4
 */

void senderos(int i, int j, int pasado, int num){
    if(N <= i || i < 0 || N <= j ||j < 0)           return;
    if(camino[i][j]==true || tablero[i][j] == '#')  return;
    if(i == N - 1 && j == M - 1){
        MAX = max(MAX, num);
        MIN = min(MIN, num);
        posible = true;
    }else{
        camino[i][j] = true;
        if( (j==0 || j==M-1) && (i!=0)) camino[i-1][j] = true;
        if( (i==0 || i==N-1) && (j!=0)) camino[i][j-1] = true;
        if(tablero[i][j] == 'I'){
            if(pasado == 1) senderos(i+1, j, 1, num+1);
            if(pasado == 2) senderos(i-1, j, 2, num+1);
            if(pasado == 3) senderos(i, j+1, 3, num+1);
            if(pasado == 4) senderos(i, j-1, 4, num+1);
        }
        if(tablero[i][j] == 'L'){
            if(pasado == 1 || pasado == 2){
                senderos(i, j+1, 3, num+1);
                senderos(i, j-1, 4, num+1);
            }
            if(pasado == 3 || pasado == 4){
                senderos(i+1, j, 1, num+1);
                senderos(i-1, j, 2, num+1);
            }
        }
        if(tablero[i][j] == '+'){
            senderos(i+1, j, 1, num+1);
            senderos(i-1, j, 2, num+1);
            senderos(i, j+1, 3, num+1);
            senderos(i, j-1, 4, num+1);
        }
        camino[i][j] = false;
        if( (j==0 || j==M-1) && (i!=0) && pasado != 1) camino[i-1][j]=false;
        if( (i==0 || i==N-1) && (j!=0) && pasado != 3) camino[i][j-1]=false;
    }
}

void solve(){
    if(tablero[0][0] == '+' ) senderos(0,0,1,0);
    else {senderos(0,0,1,0);senderos(0,0,3,0);}

    if(posible) cout << "POSIBLE " << MIN << " " << MAX << endl;
    else cout << "IMPOSIBLE" << endl;
}


int main(){
	fastio;
    int c;
    cin>>c;
    forn(t,c){
        cin >> N >> M;
        MAX = -1;
        MIN = 121;
        posible = false;
        forn(i,N) forn(j,M) cin >> tablero[i][j];
        solve();
        forn(i,N) forn(j,M) camino[i][j] = false;
    }
    return 0;
}
