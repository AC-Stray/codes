#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
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
void input(Type& arg, Types&... args){
	arg = read<Type>();
	input(args...);
}
namespace Main{
	const int N = 1e6;
	const int MOD = 998244353;
	int n, k;
	ll fac[N], ifac[N], ans;
	ll qpow(ll n, ll k){
		ll res = 1;
		while(k > 0){
			if(k & 1) res = res * n % MOD;
			n = n * n % MOD;
			k >>= 1;
		}
		return res;
	}
	ll c(int n, int k){
		if(n < k || k < 0) return 0ll;
		return fac[n] * ifac[n-k] % MOD * ifac[k] % MOD;
	}
	ll solve(int r, int b){
		if(r >= b + n) return c(r + b, r);
		if(r < b) return 0ll;
		return (c(r + b, r) - c(r + b, 2 * r - n + 1) + MOD) % MOD;
	}
	Void check(ll &x) { x -= MOD; x += (x >> 63) & MOD; }
	void Main(){
		input(n, k);
		if(k < n) return puts("0"), void();
		fac[0] = 1;
		for(int i = 1; i < N; i++) fac[i] = fac[i-1] * i % MOD;
		ifac[N-1] = qpow(fac[N-1], MOD - 2);
		for(int i = N - 2; i >= 0; i--) ifac[i] = ifac[i+1] * (i + 1) % MOD;
		for(int i = 0; i <= k; i++) check(ans += solve(i, k - i - (i == k - i)));
		write(ans);
		return;
	}
}
int main(){
	Main::Main();
	return 0;
}