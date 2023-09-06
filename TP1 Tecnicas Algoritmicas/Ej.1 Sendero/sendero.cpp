#include <iostream>
#include <algorithm>
#include "../../utilities.h"
#define rz resize
using namespace std;

int N,M;
vector<vector<char>> tablero;
vector<vector<bool>> camino;
int MAX, MIN;
bool posible;

void senderos(int i, int j, string pasado, int num){
    if(N <= i || i < 0 || N <= j ||j < 0)           return;
    if(camino[i][j]==true || tablero[i][j] == '#')  return;
    if(i == N - 1 && j == M - 1){
        MAX = max(MAX, num);
        MIN = min(MIN, num);
        posible = true;
    }else{
        camino[i][j] = true;
        if(tablero[i][j] == 'I'){
            if(pasado == "arriba") senderos(i+1, j, "arriba", num+1);
            if(pasado == "abajo") senderos(i-1, j, "abajo", num+1);
            if(pasado == "izq") senderos(i, j+1, "izq", num+1);
            if(pasado == "der") senderos(i, j-1, "der", num+1);
        }
        if(tablero[i][j] == 'L'){
            if(pasado == "arriba" || pasado == "abajo"){
                senderos(i, j+1, "izq", num+1);
                senderos(i, j-1, "der", num+1);
            }
            if(pasado == "izq" || pasado == "der"){
                senderos(i+1, j, "arriba", num+1);
                senderos(i-1, j, "abajo", num+1);
            }
        }
        if(tablero[i][j] == '+'){
            senderos(i+1, j, "arriba", num+1);
            senderos(i-1, j, "abajo", num+1);
            senderos(i, j+1, "izq", num+1);
            senderos(i, j-1, "der", num+1);
        }
        camino[i][j] = false;
    }
}

void solve(){
    senderos(0,0,"arriba",0);
    senderos(0,0,"izq",0);
    if(posible) cout << "POSIBLE " << MIN << " " << MAX << endl;
    else cout << "IMPOSIBLE" << endl;
}


int main(){
    int c;
    cin>>c;
    forn(i,c){
        cin >> N >> M;
        tablero.rz(N,vector<char>(M));
        camino.rz(N, vector<bool>(M, 0));
        MAX = -1;
        MIN = 121;
        posible = false;
        forn(i,N) forn(j,M) cin >> tablero[i][j];
        solve();
        tablero.clear(); camino.clear();
    }
    return 0;
}