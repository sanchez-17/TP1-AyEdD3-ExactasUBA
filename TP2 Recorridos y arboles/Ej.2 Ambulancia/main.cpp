#include <bits/stdc++.h>
#define ii pair<int,int>
using namespace std;
int N, M, tiempo;
vector<vector<int> > matrix;
vector<int> orden;
vector<vector<ii> > ady;
vector<int> d;//vector de distancias

const int INF = 10000000;
ii paciente, hospital;

void listady(){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(i > 0)   ady[M*i + j].push_back({M*i + j - M, matrix[i-1][j]});    //Casilla de arriba -1
            if(i < N-1) ady[M*i + j].push_back({M*i + j + M, matrix[i+1][j]});    //Casilla de abajo   +1
            if(j > 0)   ady[M*i + j].push_back({M*i + j -1, matrix[i][j-1]});    //Casilla de la izquierda
            if(j < M-1) ady[M*i + j].push_back({M*i + j +1, matrix[i][j+1]});    //Casilla de la derecha
        }
    }
}


void bfs(int s, int t){
    d[s] = t;
    queue<int> q; q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for(auto v: ady[u]){
            if (d[v.first] == INF && (d[u] + 1 < v.second || v.second==0)) {
                d[v.first] = d[u] + 1;
                q.push(v.first);
            }
        }
    }
}

int main()
{
    int c;
    cin>>c;
    for(int i = 0; i < c; i++){
        cin >> N >> M;
        matrix = vector<vector<int> >(N, vector<int>(M));
        orden = vector<int>(M*N);
        d = vector<int>(N*M, INF);
        //Ingresamos matriz
        for(int j = 0; j < N; j++)
            for(int k = 0; k < M; k++)
                cin >> matrix[j][k];
        cin >> hospital.first >> hospital.second;
        cin >> paciente.first >> paciente.second;
        //armamos lista de adyacencia
        ady = vector<vector<ii> >(N*M);
        listady();
        //Computamos camino hasta el paciente
        int p = M * paciente.first + paciente.second;
        int h = M * hospital.first + hospital.second;
        bfs(h, 0 );
        int t = d[p]; //Guardamos el tiempo de ida
        d = vector<int>(N*M, INF);
        //Computamos camino hasta el hospital
        bfs(p, t);
        if(t==INF || d[h]==INF) cout << "IMPOSIBLE" << endl;
        else cout << t << " " << d[h] << endl;

    }

    return 0;
}
