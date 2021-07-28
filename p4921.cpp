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
const int MOD = 998244353;
int t, n[200005], nmax;
int fac[5000005], g[5000005];
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
    input(t);
    for(ri i = 0; i < t; i++) input(n[i]), nmax = max(nmax, n[i]);
    fac[0] = 1;
    for(ri i = 1; i <= nmax; i++) fac[i] = 1ll * fac[i-1] * i % MOD;
    g[0] = 1, g[1] = 0;
    for(ri i = 2; i <= nmax; i++) g[i] = 1ll*4*i%MOD*(i-1)%MOD*(g[i-1]+2ll*(i-1)*g[i-2]%MOD)%MOD;
    for(ri i = 0; i < t; i++) 
    for(ri k = 0; k <= n[i]; k++)
    write(1ll*fac[n[i]]*fac[n[i]]%MOD*qpow(1ll*fac[n[i]-k]*fac[n[i]-k]%MOD*fac[k]%MOD, MOD-2)%MOD*qpow(2, k)%MOD*g[n[i]-k]%MOD), puts("");
	return 0;
}