#ifndef UTILITIES
#define UTILITIES

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <iomanip>
using namespace std;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.failbit);
#define forr(i,a,b) for(int i = (int) a; i < (int) b; i++)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i = (int) b-1; i >= (int) a; i--)
#define dforn(i,n) dforr(i,0,n)
//renombres facheros
#define rz resize
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define pb push_back
#define ppb pop_back
#define fst first
#define snd second
#define pii pair<int,int>
#define vi vector<int>
#define matriz vector<vector<int> >
//Para debugear
#define DBS(x) RAYA;cerr << (x) << endl;
#define DBG(x) cerr << #x << " = " << (x) << endl;
#define DBG2(x,y)   cerr << #x << " = " << (x) << " , " << #y << " = " << (y) << endl;
#define DBG3(x,y,z)   cerr << #x << " = " << (x) << " , " << #y << " = " << (y) << " , " << #z << " = " << (z)<< " , " << endl;
#define DBG4(x,y,z,w) cerr << #x << " = " << (x) << " , " << #y << " = " << (y) << " , " << #z << " = " << (z)<< " , " << #w << " = " << (w) << endl;
#define DBGY(x) cerr << #x << " = " << (x) << " , ";
#define RAYA cerr<<"========================="<<endl;

template<class T>
void impAux(vector<vector<T>>& M){
	int filas = M.size();
	int columnas = M[0].size();
	int max_longitud = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int longitud_actual = std::to_string(M[i][j]).length();
            if (longitud_actual > max_longitud) {
                max_longitud = longitud_actual;
            }
        }
    }

    // Imprimir la matriz con formato
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            std::cout << std::setw(max_longitud + 2) << M[i][j];
        }
        std::cout << std::endl;
    }
}

template<class T>
void impMemo(vector<vector<T>>& M){
	int n = M.size();int m = M[0].size();
	//Mostrar indices
	forn(i,m+1) cout << -i-1 << " ";
	
	forn(i,n)
	{ 
		cout << "\n" << i << " ";
		forn(j,m) cout << M[i][j] << " ";
	}
	cout << "\n";
}

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
ostream & operator <<(ostream &os, const vector<T>&v){
	os << "[";
	forn(i,sz(v)){
		if (i>0) os	<< ",";
		os << v[i];
	}
	return os << "]";
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
