#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#define forr(i,a,b) for(int i=(int)a;i<(int)b;i++)
#define forn(i,n) forr(i,0,n)
#define rz resize
#define sz size
#define pb push_back
#define ppb pop_back
#define ll long long
using namespace std;

int N,M;
vector<vector<bool> > camino;
vector<vector<char> > tablero;
int MAX, MIN;
bool posible;

void senderos(int i, int j, int pasado, int num){
    if(N <= i || i < 0 || N <= j ||j < 0){
        return;
    }
    if(camino[i][j]==true || tablero[i][j] == '#'){
        return;
    }
    if(i == N - 1 && j == M - 1){
        MAX = max(MAX, num);
        MIN = min(MIN, num);
        posible = true;
    }else{
        camino[i][j] = true;
        //guardo si camino[i-1][j] y camino[i][j-1] eran true antes
        bool arriba;
        bool izq;
        if( (j==0 || j==M-1) && (i!=0)){
            arriba = camino[i-1][j];
            camino[i-1][j] = true;
        }
        if( (i==0 || i==N-1) && (j!=0)){
            izq = camino[i][j-1];
            camino[i][j-1] = true;
        }
        if(tablero[i][j] == 'I'){
            if(pasado == 3){
                senderos(i+1, j, 3, num+1);
            }
            if(pasado == 4){
                senderos(i-1, j, 4, num+1);
            }
            if(pasado == 5){
                senderos(i, j+1, 5, num+1);
            }
            if(pasado == 6){
                senderos(i, j-1, 6, num+1);
            }
        }
        if(tablero[i][j] == 'L'){
            if(pasado == 3 || pasado == 4){
                senderos(i, j+1, 5, num+1);
                senderos(i, j-1, 6, num+1);
            }
            if(pasado == 5 || pasado == 6){
                senderos(i+1, j, 3, num+1);
                senderos(i-1, j, 4, num+1);
            }
        }
        if(tablero[i][j] == '+'){
            senderos(i-1, j, 4, num+1);
            senderos(i, j-1, 6, num+1);
            senderos(i, j+1, 5, num+1);
            senderos(i+1, j, 3, num+1);
        }
        camino[i][j] = false;
        if( (j==0 || j==M-1) && (i!=0)){
            if(!arriba){
                camino[i-1][j] = false;
            }
        }
        if( (i==0 || i==N-1) && (j!=0)){
            if(!izq){
                camino[i][j - 1] = false;
            }
        }
    }
}

void solve(){
    if(tablero[N-1][M-1] == '#'){
        cout<< "IMPOSIBLE" << endl;
        return;
    }
    if(tablero[0][0] == '+' ) {
        senderos(0, 0, 3, 0);
    }else{
        senderos(0,0,3,0);
        senderos(0,0,5,0);
    }
    if(posible){
        cout << "POSIBLE " << MIN << " " << MAX << endl;
    }else{
        cout << "IMPOSIBLE" << endl;
    }
}


int main(){
    int c;
    cin>>c;
    forn(x,c){
        cin >> N >> M;
        tablero.rz(N,vector<char>(M));
        camino.rz(N, vector<bool>(M, 0));
        MAX = -1;
        MIN = 121;
        posible = false;
        forn(i,N) forn(j,M) cin >> tablero[i][j];
        solve();
    }
    return 0;
}

