#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int MOD = 20101009;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-10;
const int N = 10000005;
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
	int n, m, inv;
	int cnt, pri[N>>3], mu[N];
	bool vis[N];
	ll ans, s[N];
//	Void check(int &x) { x -= MOD; x += x >> 31 & MOD; }
	Void check(ll &x) { x -= MOD; x += x >> 63 & MOD; }
	LL sigma(ll x) { return x * (x + 1) % MOD * inv % MOD; }
	void initMu(){
		mu[1] = 1;
		for(ri i = 2; i <= n; i++){
			if(!vis[i]){
				pri[cnt++] = i;
				mu[i] = MOD - 1;
			}
			for(ri j = 0; j < cnt; j++){
				if(i * pri[j] > n) break;
				vis[i * pri[j]] = true;
				if(i % pri[j] == 0) break;
				mu[i * pri[j]] = MOD - mu[i];
			}
		}
		for(ri i = 1; i <= n; i++) check(s[i] = s[i-1] + mu[i] * i % MOD * i % MOD);
	}
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
		input(n, m);
		if(n > m) swap(n, m);
		initMu();
		inv = qpow(2, MOD - 2);
		for(ri i = 1; i <= n; i++){
			int x = n / i, y = m / i;
			ll sum = 0;
			for(ri j = 1, r; j <= x; j = r + 1){
				r = min(x / (x / j), y / (y / j));
				sum = (sum + (s[r] - s[j-1] + MOD) % MOD * sigma(x/j) % MOD * sigma(y/j) % MOD) % MOD;
			}
			ans = (ans + sum * i % MOD) % MOD;
		}
		write(ans);
		return;
	}
} // namespace
signed main(){
#ifdef Liuxizai
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif // Liuxizai
	Main::Main();
	return 0;
}

