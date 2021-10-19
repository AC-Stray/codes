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
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int N = 100000;
const int _N = 100005;
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
	int x, t, n, a, s, pri[_N], cnt;
	bool vis[_N];
	void init(){
		for(ri i = 2; i <= N; i++){
			if(!vis[i]) pri[cnt++] = i;
			for(ri j = 0; j < cnt; j++){
				if(i * pri[j] > N) break;
				vis[i * pri[j]] = true;
				if(i % pri[j] == 0) break;
			}
		}
	}
	ll qpow(ll x, ll k){
		ll res = 1;
		while(k > 0){
			if(k & 1) res = res * x % n;
			x = x * x % n;
			k >>= 1; 
		}
		return res;
	}
	void Main(){
		input(x, t);
		if(x == 2) init();
		while(t--){
			input(n);
			if(x == 1){
				if(n&1 && n^1){
					puts("0");
					continue;
				}
				write(2); putchar(' ');
				for(ri i = 0; i < n; i++){
					if(i&1) write(i);
					else write(n-i);
					putchar(' ');
				}
				puts("");
			}
			else{
				if(n == 4){
					puts("2 1 3 2 4");
					continue;
				}
				if(vis[n]){
					puts("0");
					continue;
				}
				write(2); putchar(' ');
				write(1); putchar(' ');
				s = 1;
				for(ri i = 1; i < n - 1; i++){
					write(a=(s+1)%n); putchar(' ');
					s = s * qpow(a, n - 2) % n;
				}
				write(n); putchar(' ');
				puts("");
			}
		}
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

