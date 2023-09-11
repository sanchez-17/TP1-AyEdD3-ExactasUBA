#include <iostream>
#include <algorithm>
using namespace std;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.failbit);
#define forr(i,a,b) for(int i = (int) a; i < (int) b; i++)
#define forn(i,n) forr(i,0,n)
#define DBG4(x,y,z,w) cerr << #x << " = " << (x) << " , " << #y << " = " << (y) << " , " << #z << " = " << (z)<< " , " << #w << " = " << (w) << endl;

int N,M;
const int MAX_N = 121, MAX_M = 121;
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

bool todaFilaRecorrida(int fila) {
    forn(j, M) if (!camino[fila][j]) return false;
    return true;
}

bool todaColRecorrida(int col) {
    forn(i, M) if (!camino[i][col]) return false;
    return true;
}

void senderos(int i, int j, int desde, int num){

    if(i < 0 || N <= i || N <= j ||j < 0)           return;
    if(camino[i][j]==true || tablero[i][j] == '#')  return;
    if(i == N - 1 && j == M - 1){
        MAX = max(MAX, num);
        MIN = min(MIN, num);
        posible = true;
        return;
    }else{
        camino[i][j] = true;bool a,b;
        a = b = false;
        if( (j==0 || j==M-1) && (i!=0) && desde != 1 && todaFilaRecorrida(i) && !camino[i-1][j]) {camino[i-1][j] = true;a = true;}
        if( (i==0 || i==N-1) && (j!=0) && desde != 3 && todaColRecorrida(j) && !camino[i][j-1]) {camino[i][j-1] = true;b = true;}
        if(tablero[i][j] == 'I'){
            if(desde == 1) senderos(i+1, j, 1, num+1);
            if(desde == 2) senderos(i-1, j, 2, num+1);
            if(desde == 3) senderos(i, j+1, 3, num+1);
            if(desde == 4) senderos(i, j-1, 4, num+1);
        }
        if(tablero[i][j] == 'L'){
            if(desde == 1 || desde == 2){
                senderos(i, j+1, 3, num+1);
                senderos(i, j-1, 4, num+1);
            }
            if(desde == 3 || desde == 4){
                senderos(i+1, j, 1, num+1);
                senderos(i-1, j, 2, num+1);
            }
        }
        if(tablero[i][j] == '+'){
			senderos(i+1, j, 1, num+1);
            senderos(i, j+1, 3, num+1);
            senderos(i-1, j, 2, num+1);
            senderos(i, j-1, 4, num+1);
        }
        camino[i][j] = false;
        if(a) camino[i-1][j]=false;
        if(b) camino[i][j-1]=false;
    }
}

void solve(){
    if(tablero[N-1][M-1] == '#'){
        cout<< "IMPOSIBLE" << endl;
        return;
    }
    senderos(0,0,1,0);
    if(tablero[0][0] != '+' ) senderos(0,0,3,0);
    
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
