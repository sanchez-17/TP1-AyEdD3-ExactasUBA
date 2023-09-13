#include <iostream>
#include <vector>
#include <string>
#include <string>
using namespace std;
#define fastio ios_base::sync_with_stdio(0); cin.tie(0); cin.exceptions(cin.failbit);
#define forr(i,a,b) for(int i = (int) a; i < (int) b; i++)
#define forn(i,n) forr(i,0,n)
#define dforr(i,a,b) for(int i = (int) b-1; i >= (int) a; i--)
#define dforn(i,n) dforr(i,0,n)
#define fst first
#define snd second


int m, N, W, sumaMax;vector<int> acum;
int MAX_W = 1e3, MAX_N = 1e2;
string RES;
int libro[100];
vector<vector<pair<bool,char>>> memo ;
//bool memo[100][100 * 1000][2] = {{{false}}};


void calcularRes(string& res){
    forn(i, res.size()) if(res[i] != RES[i]) RES[i] = '?';
}

bool f(int i, int sum, string& res ){
    if(i == N) if (sum == W) {
            //Llegue a una solucion valida y debo saber si habia una antes
            if(RES.size() == 0) RES = res;
            else             calcularRes(res);
            return true;
        }else   return false;
    else{
        //if(memo[i][sum + sumaMax].fst) if (memo[i][sum + sumaMax].snd != '-') return memo[i][sum + sumaMax].snd == 'n';
        //Pruebo restando
        res.push_back('-');
        bool a = f(i+1, sum-libro[i], res);
        res.pop_back();
        //Pruebo sumando
        res.push_back('+');
        bool b = f(i+1, sum+libro[i], res);
        res.pop_back();
        bool r; //=  a || b;


        if(a && b) r = '?'; //?
        else if(a) r = '-'; //-
        else if(b) r = '+'; //+
        else r = 'n';


        memo[i][sum + sumaMax].fst = true;
        memo[i][sum + sumaMax].snd = r;
        return r;
    }

}

int main(){
    cin>>m;
    forn(c,m){
        cin >> N >> W;
        W = W / 100;
        forn(i, N) {
            int x;
            cin >> x;
            libro[i] = x / 100;
        }
        //Vemos el rango
        acum = vector<int>(N + 1, 0);
        dforn(i, N) acum[i] = acum[i + 1] + libro[i];
        sumaMax = 0;
        forn(i, N) sumaMax += libro[i];
        memo = vector<vector<pair<bool,char>>>(N+1,vector<pair<bool,char>>(sumaMax * 2 + 1,make_pair(false,'n')));
        string res;
        f(0, 0, res);
        for(char c:RES) cout << c;
        cout << '\n';
        RES = "";
    }
    return 0;
}
