#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int MOD = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-10;
const int N = 1000005;
template<typename T>
inline T read(){
	T n = 0; int f = 1; char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		n = n * 10 + ch - '0';
		ch = getchar();
	}
	return f * n;
}
template<typename T>
void write(T n){
	if(n/10) write(n/10);
	putchar(n%10+'0');
}
void input() {}
template<typename Type, typename... Types>
void input(Type &arg, Types&... args){
	arg = read<Type>();
	input(args...);
}
namespace Main{
	ll n, k, ans, pre[N], suf[N], fac[N], val[N];
	ll qpow(ll n, ll k){
		ll res = 1;
		while(k > 0){
			if(k & 1) res = res * n % MOD;
			n = n * n % MOD;
			k >>= 1;
		}
		return res;
	}
	void Main(){
		input(n, k);
		fac[0] = pre[0] = suf[k + 3] = 1;
		for(ri i = 1; i <= k + 2; i++) fac[i] = fac[i-1] * i % MOD;
		for(ri i = 1; i <= k + 2; i++) pre[i] = pre[i-1] * (n - i + MOD) % MOD;
		for(ri i = k + 2; i >= 0; i--) suf[i] = suf[i+1] * (n - i + MOD) % MOD;
		for(ri i = 1; i <= k + 2; i++) val[i] = (val[i-1] + qpow(i, k)) % MOD;
		for(ri i = 1; i <= k + 2; i++){
			ll a = ((k-i+2)&1 ? -1 : 1) * fac[k-i+2] % MOD * fac[i-1] % MOD + MOD;
			ll b = pre[i-1] % MOD * suf[i+1] % MOD;
			ans = (ans + val[i] * qpow(a, MOD - 2) % MOD * b % MOD) % MOD;
		}
		write(ans);
		return;
	}
} // namespace
int main(){
#ifdef Liuxizai
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif // Liuxizai
	Main::Main();
	return 0;
}

