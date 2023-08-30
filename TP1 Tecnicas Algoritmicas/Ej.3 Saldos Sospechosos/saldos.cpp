#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
#define forr(i,a,b) for(int i=(int)a;i<(int)b;i++)
#define fors(i,a,b) for(int i=(int)a;i>=(int)b;i--)
#define dfor(i,n) fors(i,n,0)
#define forn(i,n) forr(i,0,n)
#define rz resize
#define sz(V) V.size()
#define pb push_back
#define ppb pop_back

int m,N,W;vector<int> libro;vector<int>RES;
vector<int> Acum;
void solve(int i,int  ){
    
}

int main(){
    cin>>m;
    forn(i,m){
        cin>>N>>W;libro.rz(N);Acum.rz(N+1,0);
        forn(i,N) cin >> libro[i];
        dfor(i,N-1) Acum[i] = libro[i] + Acum[i+1];
        solve();
        impVector(RES);
    }
	return 0;
}
