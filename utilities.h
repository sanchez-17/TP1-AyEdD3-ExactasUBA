#ifndef UTILITIES
#define UTILITIES

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
#define forr(i,a,b) for(int i=(int)a;i<(int)b;i++)
#define forn(i,n) forr(i,0,n)
#define rz resize
#define sz(V) V.size()
#define pb push_back
#define ppb pop_back
#define fst first
#define snd second

template<class T>
void impMatriz(vector<vector<T>>& M){
	int n = M.size();int m = M[0].size();
	forn(i,n)
	{ 
		cout << "\n";
		forn(j,m) cout << M[i][j] << " ";
	}
	cout << "\n";
}
template<class T>
void impVector(vector<T>& V){
	int n = V.size();
	cout << "\n"<<"V:";
	forn(i,n) cout<<V[i]<<" ";
	cout << "\n";
}

template<class T>
void impVectorTuplas(vector<T>& V){
    int n = V.size();
    cout << "\n"<<"V:";
    forn(i,n) cout<< "("<<V[i].fst << "," << V[i].snd<<")" << ",";
    cout << "\n";
}
bool porFila(vector<vector<int>>& C,int sum){
		int n = sz(C),sumFila;
		bool res = true;
		forn(i,n){
			sumFila = 0;
			forn(j,n) sumFila += C[i][j];
			res = res && sumFila==sum;
		}
		return res;
}

bool porColumna(vector<vector<int>>& C,int sum){
		int n = sz(C),sumFila;
		bool res = true;
		forn(i,n){
			sumFila = 0;
			forn(j,n) sumFila += C[j][i];
			res = res && sumFila==sum;
		}
		return res;
}

bool porDiagonal(vector<vector<int>>& C,int sum){
		int n = sz(C);
		int diagI = 0;
		int diagD = 0;
		forn(i,n) {
			diagI += C[i][i];
			diagD += C[i][n-i-1];
		}
		return diagI == sum && diagD == sum;
}

bool esMagico(vector<vector<int>>& C){
		int n = sz(C);
		int sumMag = (pow(3,n) + n) / 2;
		return  porFila(C,sumMag) && porColumna(C,sumMag) && porDiagonal(C,sumMag);
}
#endif
