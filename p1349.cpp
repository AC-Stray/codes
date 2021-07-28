#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<vector>
#include<set>
#include<queue>
#include<string>
#include<cstring>
#include<map>
#include<list>
#include<deque>
#include<cctype>
#include<climits>
#include<cmath>
#include<ctime>
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
int p, q, a1, a2, n, MOD;
struct matrix{
    ll v[105][105];
    int size;
    Void init(){
        for(ri i = 0; i < size; i++) v[i][i] = 1;
    }
    matrix operator * (const matrix &b){
        matrix res(size);
        for(ri i = 0; i < size; i++) for(ri j = 0; j < size; j++) for(ri k = 0; k < size; k++)
            res.v[i][j] = (res.v[i][j] + v[i][k] * b.v[k][j] % MOD) % MOD;
        return res;
    }
    Void operator *= (const matrix &b){
        *this = *this * b;
    }
    ll* operator [] (const int &index){
        return v[index];
    }
    matrix(){
        memset(v, 0, sizeof(v));
    }
    matrix(int size): size(size){
        memset(v, 0, sizeof(v));
    }
}A(2);
matrix quickPower(matrix a, ll k){
    matrix res(a.size);
    res.init();
    while(k){
        if(k & 1) res *= a;
        a *= a;
        k >>= 1;
    }
    return res;
}
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
Void input() {}
template<typename Type, typename... Types>
Void input(Type& arg, Types&... args){
    arg = read();
    input(args...);
}
int main(){
    input(p, q, a1, a2, n, MOD);
    A[0][0] = 0;
    A[0][1] = q;
    A[1][0] = 1;
    A[1][1] = p;
    A = quickPower(A, n-2);
    write((A[0][1]*a1%MOD+A[1][1]*a2%MOD)%MOD);
	return 0;
}