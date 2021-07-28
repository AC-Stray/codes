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
const int MOD = 1e9+7;
ll k;
ll INIT[15][15] = {
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1}
};
int ans, dp[1000005][15];
int B[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
struct matrix{
    ll v[15][15];
    matrix operator * (const matrix &b){
        matrix res;
        memset(res.v, 0, sizeof(res.v));
        for(ri i = 0; i < 10; i++) for(ri j = 0; j < 10; j++) for(ri k = 0; k < 10; k++)
            res.v[i][j] = (res.v[i][j] + v[i][k] * b.v[k][j] % MOD) % MOD;
        return res;
    }
    matrix(){
        for(ri i = 0; i < 10; i++) for(ri j = 0; j < 10; j++) v[i][j] = INIT[i][j];
    }
}A;
matrix quickPower(matrix a, ll k){
    matrix t;
    while(k > 0){
        if(k & 1) t = a * t;
        a = a * a;
        k >>= 1;
    }
    return t;
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
int main(){
    k = read();
    /***********************30pts***********************
    for(ri i = 0; i <= 9; i++) dp[1][i] = 1;
    for(ri i = 2; i <= k; i++) for(ri j = 0; j <= 9; j++) for(ri k = -2; k <= 2; k++){
        if(j+k < 0 || j+k > 9) continue;
        if(i == 2 && j+k == 0) continue;
        dp[i][j] = (dp[i][j] + dp[i-1][j+k]) % MOD;
    }
    for(ri i = 0; i <= 9; i++) ans = (ans + dp[k][i]) % MOD;
    write(ans);
    ***************************************************/
    if(k == 1) {
        cout << 10;
        return 0;
    }
    A = quickPower(A, k-2);
    for(ri i = 0; i < 10; i++) for(ri j = 0; j < 10; j++){
        ans = (ans + A.v[j][i] * B[j] % MOD) % MOD;
//        cout << A.v[i][j] << ' ';
//        if(j == 9) cout << endl;
    }
    write(ans);
    puts("");
	return 0;
}