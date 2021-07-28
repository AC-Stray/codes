#include<bits/stdc++.h>
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
ull m, a, c, x0, n, g;
inline unsigned long long read(){
	ull n = 0; int f = 1; char ch = getchar();
	while('0' > ch || ch > '9') ch = getchar();
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
inline unsigned long long smul(ull a, ull b){
    ull res = 0, t = a;
    while(b > 0){
        if(b & 1) res = (res + t) % m;
        t = (t + t) % m;
        b >>= 1;
    }
    return res;
}
struct matrix{
    ull v[105][105];
    Void init(){
        for(ri i = 0; i < 2; i++) v[i][i] = 1;
    }
    Void print(){
        cout << v[0][0] << ' ' << v[0][1] << endl << v[1][0] << ' ' << v[1][1] << endl;
    }
    matrix operator * (const matrix &b){
        matrix res;
        for(ri i = 0; i < 2; i++) for(ri j = 0; j < 2; j++) for(ri k = 0; k < 2; k++)
            res.v[i][j] = (res.v[i][j] + smul(v[i][k], b.v[k][j])) % m;
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
	input(m, a, c, x0, n, g);
	A = matrix();
	A.v[0][0] = a, A.v[0][1] = 0, A.v[1][0] = c, A.v[1][1] = 1;
	A = quickPower(A, n);
    x0 %= m;
	write((smul(A.v[0][0], x0)+A.v[1][0])%m%g);
	return 0;
}