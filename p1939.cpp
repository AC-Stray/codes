#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<vector>
#include<set>
#include<queue>
#include<map>
#include<list>
#include<deque>
#include<cctype>
#include<climits>
#include<cmath>
#include<ctime>
#include<cstring>
#include<algorithm>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
const int MOD = 1e9+7;
ll t, n;
LL read(){
	ll n = 0; int f = 1; char ch = getchar();
	while('0' > ch || ch > '9'){
		if(ch == '-') f *= -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9'){
		n = (n << 1) + (n << 3) + ch-'0';
		ch = getchar();
	}
	return f * n;
}
Void write(ll x){
	if(x/10) write(x/10);
	putchar(x%10+'0');
}
struct matrix{
    ll v[105][105];
    Void input(){
        for(ri i = 0; i < n; i++) for(ri j = 0; j < n; j++) v[i][j] = read();
    }
    Void output(){
        for(ri i = 0; i < n; i++){
            for(ri j = 0; j < n; j++) write(v[i][j]), putchar(' ');
            puts("");
        }
    }
    Void init(){
        for(ri i =  0; i < 3; i++) v[i][i] = 1;
    }
    matrix operator * (const matrix &b){
        matrix res;
        for(ri i = 0; i < 3; i++) for(ri j = 0; j < 3; j++) for(ri k = 0; k < 3; k++)
            res.v[i][j] = (res.v[i][j] + v[i][k] * b.v[k][j] % MOD) % MOD;
        return res;
    }
    matrix(){
        memset(v, 0, sizeof(v));
    }
}A;
matrix quickPower(matrix a, ll k){
    matrix t;
    t.init();
    while(k > 0){
        if(k & 1) t = a * t;
        a = a * a;
        k >>= 1;
    }
    return t;
}
int main(){
    t = read();
    while(t--){
        n = read();
        A = matrix();
        A.v[1][0] = A.v[2][1] = A.v[0][2] = A.v[2][2] = 1;
        A = quickPower(A, n-3);
        write((A.v[2][0]+A.v[2][1]+A.v[2][2])%MOD);
        puts("");
    }
	return 0;
}