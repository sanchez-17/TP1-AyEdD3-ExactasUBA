#include <iostream>
#include <vector>
using namespace std;
int c,N;
bool IMPOSIBLE;
vector<vector<int>> M, ady;

void FW(){
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (ady[i][k] + ady[k][j] < ady[i][j])
					ady[i][j] = ady[i][k] + ady[k][j];
}

void solve(){
	for(int k = 0; k < N; k++)
		for(int i = 1; i < N; i++)
				for(int j = 0; j < i; j++){
					if(M[i][j] > M[i][k] +M[k][j]){
						IMPOSIBLE = true;
					}
				}
	if(IMPOSIBLE) cout << "IMPOSIBLE" << endl;
	else cout << "POSIBLE" << endl;
				
}

int main(){
	cin >> c;
	while(c > 0){
		IMPOSIBLE = false;
		cin >> N;
		ady = vector<vector<int>>(N, vector<int>(N, 0));
		M = vector<vector<int>>(N, vector<int>(N, 0));
		for(int i = 1; i < N; i++)
			for(int j = 0; j < i; j++){
				int value;
				cin >> value;
				M[i][j] = value;
				M[j][i] = value;
			}
		solve();
		c--;
	}
	
}
