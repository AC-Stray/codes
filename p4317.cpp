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
const int MOD = 1e7 + 7;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-10;
const int N = 105;
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
	ll n, ans, dp[N][N][N], num[N], len;
	ll qpow(ll n, ll k){
		ll res = 1;
		while(k > 0){
			if(k & 1) res = res * n % MOD;
			n = n * n % MOD;
			k >>= 1;
		}
		return res;
	}
	ll dfs(int pos, int st, int d, bool limit){
		if(st > d) return 0;
		if(!pos) return st == d;
		if(!limit && ~dp[pos][st][d]) return dp[pos][st][d];
		ll res = 0;
		int ed = limit ? num[pos] : 1;
		for(ri i = 0; i <= ed; i++) res += dfs(pos-1, st+(i==1), d, limit&&i==num[pos]);
		return dp[pos][st][d] = res;
	}
	void Main(){
		input(n);
		while(n){
			num[++len] = n & 1;
			n >>= 1;
		}
		ans = 1;
		for(ri i = 1; i <= len; i++){
			memset(dp, -1, sizeof(dp));
			ans = ans * qpow(i, dfs(len, 0, i, true)) % MOD;
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

