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
const int MOD = 1004535809;
const int inf = 0x3f3f3f3f;
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
	ll n, a[N], sum[N], f[N][N][N], inv[N], fac[N], ifac[N];
	void Main(){
		input(n);
		for(ri i = 1; i <= n; i++) input(a[i]), a[i]--, sum[i] = sum[i-1] + a[i];
		inv[0] = inv[1] = fac[0] = ifac[0] = 1;
		for(ri i = 2; i <= n; i++) inv[i] = (MOD-MOD/i) * inv[MOD%i] % MOD;
		for(ri i = 1; i <= n; i++) fac[i] = fac[i-1] * i % MOD;
		for(ri i = 1; i <= n; i++) ifac[i] = ifac[i-1] * inv[i] % MOD;
		f[0][0][0] = 1;
		for(ri i = 1; i <= n; i++){
			for(ri j = 0; j <= i; j++){
				for(ri k = 0; k <= min(sum[i-1], n-2); k++){
					for(ri l = 0; l <= min(a[i], n-2-k); l++){
						if(j) f[i][j][k+l] = (f[i][j][k+l] + f[i-1][j-1][k] * ifac[l] % MOD) % MOD;
						if(l == 0) f[i][j][k] = (f[i][j][k] + f[i-1][j][k]) % MOD;
					}
				}
			}
		}
		write(n), putchar(' ');
		for(ri i = 2; i <= n; i++) write(f[n][i][i-2] * fac[i-2] % MOD), putchar(' ');
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

