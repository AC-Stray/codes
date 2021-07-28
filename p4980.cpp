#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
const int MOD = 1e9+7;
int t, n;
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
Int phi(int x){
    int rt = x, yx = x;
    for(ri i = 2; i * i <= yx; i++){
        if(x % i == 0){
            rt = rt * (i-1) / i % MOD;
            while(x % i == 0) x /= i;
        }
    }
    if(x > 1) rt = rt * (x-1) / x;
    return rt;
}
LL qpow(int a, int k){
    ll rt = 1, t = a;
    while(k > 0){
        if(k & 1) rt = (ll)rt * t % MOD;
        t = t * t % MOD;
        k >>= 1;
    }
    return rt;
}
signed main(){
    input(t);
    while(t--){
        input(n);
        int ans = 0;
        for(ri i = 1; i * i <= n; i++){
            if(n % i != 0) continue;
            ans = (ans + (ll)qpow(n, i) * phi(n/i) % MOD) % MOD;
            if(i * i != n) ans = (ans + (ll)qpow(n, n/i) * phi(i) % MOD) % MOD;
        }
        write(ans*qpow(n, MOD-2)%MOD), puts("");
    }
	return 0;
}