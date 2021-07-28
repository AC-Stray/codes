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
const int N = 2005;
ll n, a, k;
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
	ll aPow, aInv, sum, pw[N], c[N], s[N];
	ll qpow(ll n, ll k){
		ll res = 1;
		n %= MOD;
		while(k > 0){
			if(k & 1) res = res * n % MOD;
			n = n * n % MOD;
			k >>= 1;
		}
		return res;
	}
	void Main(){
		aPow = qpow(a, n + 1);
		aInv = qpow(a - 1, MOD - 2);
		pw[0] = c[0] = 1;
		for(ri i = 1; i <= k; i++) pw[i] = pw[i-1] * ((n + 1) % MOD) % MOD;
		for(ri i = 0; i <= k; i++){
			for(ri j = 1; j < i; j++) c[j] = c[j-1] * (i - j + 1) % MOD * qpow(j, MOD - 2) % MOD;
			sum = 0;
			for(ri j = 0; j < i; j++) sum = (sum + c[j] * s[j] % MOD) % MOD; 
			s[i] = (pw[i] * aPow % MOD - a * sum % MOD + MOD - a + MOD) % MOD * aInv % MOD;
		}
		write(s[k]);
		return;
	}
} // namespace
namespace Main2{
	ll ans, pre[N], suf[N], fac[N], val[N];
	ll qpow(ll n, ll k){
		ll res = 1;
		n %= MOD;
		while(k > 0){
			if(k & 1) res = res * n % MOD;
			n = n * n % MOD;
			k >>= 1;
		}
		return res;
	}
	void Main(){
		fac[0] = pre[0] = suf[k + 3] = 1;
		for(ri i = 1; i <= k + 2; i++) fac[i] = fac[i-1] * i % MOD;
		for(ri i = 1; i <= k + 2; i++) pre[i] = pre[i-1] * (n - i + MOD) % MOD;
		for(ri i = k + 2; i >= 0; i--) suf[i] = suf[i+1] * (n - i + MOD) % MOD;
		for(ri i = 1; i <= k + 2; i++) val[i] = (val[i-1] + qpow(i, k) % MOD) % MOD;
		for(ri i = 1; i <= k + 2; i++){
			ll x = ((k-i+2)&1 ? -1 : 1) * fac[k-i+2] % MOD * fac[i-1] % MOD + MOD;
			ll y = pre[i-1] % MOD * suf[i+1] % MOD;
			ans = (ans + val[i] * qpow(x, MOD - 2) % MOD * y % MOD) % MOD;
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
	input(n, a, k);
	if(a == 1) Main2::Main();
	else Main::Main();
	return 0;
}

