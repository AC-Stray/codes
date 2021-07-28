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
const int MOD = 1e8+7;
int n, m, t, A[1000005];
int dp[1000005];
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
ll qpow(int a, int k){
    ll res = 1, tmp = a;
    while(k > 0){
        if(k&1) res = res * tmp % MOD;
        tmp = tmp * tmp % MOD;
        k >>= 1;
    }
    return res;
}
int main(){
    input(n, m);
    t = qpow(2, n);
    A[0] = 1;
    for(ri i = 1; i <= m; i++) A[i] = 1ll * A[i-1] * (t-i+MOD) % MOD;
    // for(ri i = 0; i <= m; i++) cout << A[i] << ' '; cout << endl;
    dp[0] = 1, dp[1] = 0;
    for(ri i = 2; i <= m; i++) dp[i] = (1ll * A[i-1] - dp[i-1] + MOD - 1ll*dp[i-2]*(i-1)%MOD*(t-i+1+MOD)%MOD + MOD) % MOD;
    t = 1;
    for(ri i = 2; i <= m; i++) t = 1ll * t * i % MOD;
    write(1ll * dp[m] * qpow(t, MOD-2) % MOD);
	return 0;
}