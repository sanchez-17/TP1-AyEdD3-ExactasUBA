#include <iostream>
#include <vector>
using namespace std;
int c,N;
const int INF = 1e6;
bool IMPOSIBLE;
vector<vector<int>> M, ady;

/*
 * Idea:
 * Chequeamos si la matriz de entrada M es FW(Ej. 13 Practica 4). Representa la matriz de caminos minimos entre los nodos
 * Si lo es, armamos el grafo resultante en G'= (V,E) = Ady donde para toda arista e in E: w(e) = 1.
 * Luego aplicamos Floyd-Warshall sobre G' para obtener la matriz que retornamos como respuesta. Pues representa los caminos minimos(cant de aristas minimas) entre los nodos.
 *
 */

void FW(){
    for(int k = 0; k < N; k++)
        for(int i = 1; i < N; i++)
            for(int j = 0; j < i; j++)
                ady[i][j] = ady[j][i] = min(ady[i][j], ady[i][k] + ady[k][j]);
}

void solve(){
    for(int k = 0; k < N; k++)
        for(int i = 1; i < N; i++)
            for(int j = 0; j < i; j++){
                if(M[i][j] > M[i][k] + M[k][j]){
                    IMPOSIBLE = true;
                }
            }
    if(IMPOSIBLE) cout << "IMPOSIBLE" << endl;
    else cout << "POSIBLE" << endl;

    if(!IMPOSIBLE){
        for(int k = 0; k < N; k++){
            for(int i = 1; i < N; i++){
                for(int j = 0; j < i; j++){
                    if(k != i && k != j && M[i][j] == M[i][k] + M[k][j]){
                        ady[i][j] = ady[j][i] = INF;
                    }
                }
            }
        }
        FW();
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                cout<<ady[i][j];
                if(j != N-1){
                    cout<<" ";
                }
            }
            cout<<endl;
        }
    }
}

int main(){
    cin >> c;
    while(c > 0){
        IMPOSIBLE = false;
        cin >> N;
        ady = vector<vector<int>>(N, vector<int>(N, 1));
        for(int i = 0; i < N; i++){//Ponemos ceros en la diagonal de Ady
            ady[i][i] = 0;
        }
        M = vector<vector<int>>(N, vector<int>(N, 0));
        for(int i = 1; i < N; i++) {
            for(int j = 0; j < i; j++){
                int value;
                cin >> value;
                M[i][j] = M[j][i] = value;
            }
        }
        solve();
        c--;
    }

}
