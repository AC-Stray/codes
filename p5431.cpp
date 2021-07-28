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
ll n, p, k, tk, ans, a[5000005], pre[5000005], suf[5000005];
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
LL quickPower(ll a, ll k, ll mod){
    ll res = 1;
    while(k > 0){
        if(k & 1) res = res * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return res;
}
int main(){
    input(n, p, k);
    pre[0] = suf[n+1] = 1;
    tk = 1;
    for(ri i = 1; i <= n; i++) input(a[i]);
    for(ri i = 1; i <= n; i++) pre[i] = pre[i-1] * a[i] % p;
    for(ri i = n; i >= 1; i--) suf[i] = suf[i+1] * a[i] % p;
    for(ri i = 1; i <= n; i++) tk = tk * k % p, ans = (ans + tk * pre[i-1] % p * suf[i+1] % p) % p;
    ans = quickPower(pre[n], p-2, p) * ans % p;
    write(ans);
	return 0;
}