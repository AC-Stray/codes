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
const int MOD = 1e9+7;
ll t, a, b, h;
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
LL quickPower(ll a, ll k, int mod){
    ll res = 1;
    while(k > 0){
        if(k & 1) res = res * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return res;
}
int main(){
    input(t);
    while(t--){
        input(a, b, h);
        if(b == 1) write(((a-1)*h+a)%MOD), puts("");
        else if(a <= b) write(quickPower(b, h, MOD) * a % MOD), puts("");
        else write(((quickPower(b, h, MOD)-1)*quickPower(b-1, MOD-2, MOD)%MOD*(a-b)%MOD+quickPower(b, h, MOD)*a%MOD)%MOD), puts("");
    }
	return 0;
}