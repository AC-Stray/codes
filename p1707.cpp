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
typedef __int128_t TYPE;
ull n, m;
int p, q, r, t, u, v, w, x, y, z;
struct matrix{
    TYPE value[105][105] = {
        {0, q, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, p, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, v, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, u, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, y, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, x, 0, 0, 0, 0, 0},
        {0, r, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, t, 0, 0, 0, 1, 2, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, w, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, z, 0},
        {0, 1, 0, 0, 0, 2, 1, 1, 0, 0, 1}
    };
    int size = 11;
    Void init(){
        memset(value, 0, sizeof(value));
        for(ri i = 0; i < size; i++) value[i][i] = 1;
    }
    Void output(){
        for(ri i = 0; i < size; i++){
            for(ri j = 0; j < size; j++) cout << (ll)value[i][j] << ' ';
            cout << endl;
        }
        cout << endl;
    }
    matrix operator * (const matrix &b){
        matrix res;
        memset(res.value, 0, sizeof(res.value));
        for(ri i = 0; i < size; i++) for(ri j = 0; j < size; j++) for(ri k = 0; k < size; k++)
            res.value[i][j] = (res.value[i][j] + value[i][k] * b.value[k][j] % m) % m;
        return res;
    }
    Void operator *= (const matrix &b){
        *this = *this * b;
    }
    TYPE* operator [] (const int &index){
        return value[index];
    }
};
matrix quickPower(matrix a, ull k){
    matrix res;
    res.init();
    while(k > 0){
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
    input(n, m, p, q, r, t, u, v, w, x, y, z);
    ull start[] = {1, 3, 1, 3, 1, 3, 1, 1, (ull)w, (ull)z, 1};
    matrix A;
    // A.output();
    A = quickPower(A, n-2);
    // A.output();
    __int128_t ans;
    /******************nodgd******************/
    ans = 0;
    for(ri i = 0; i < 11; i++) ans = (ans + A[i][1] * start[i] % m) % m;
    cout << "nodgd " << (ll)ans << endl;
    /******************Ciocio******************/
    ans = 0;
    for(ri i = 0; i < 11; i++) ans = (ans + A[i][3] * start[i] % m) % m;
    cout << "Ciocio " << (ll)ans << endl;
    /******************Nicole******************/
    ans = 0;
    for(ri i = 0; i < 11; i++) ans = (ans + A[i][5] * start[i] % m) % m;
    cout << "Nicole " << (ll)ans << endl;
	return 0;
}