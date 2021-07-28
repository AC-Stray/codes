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
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-10;
const int _N = 50100;
const int N = 50005;
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
	int n, a, b, d, ans;
	int cnt, pri[_N], mu[_N], s[_N];
	bool vis[_N];
	void init(){
		mu[1] = 1;
		for(ri i = 2; i <= N; i++){
			if(!vis[i]){
				pri[cnt++] = i;
				mu[i] = -1;
			}
			for(ri j = 0; j < cnt; j++){
				if(i * pri[j] > N) break;
				vis[i * pri[j]] = true;
				if(i % pri[j] == 0) break;
				mu[i * pri[j]] = -mu[i];
			}
		}
		for(ri i = 1; i <= N; i++) s[i] = s[i-1] + mu[i];
	}
	void Main(){
		init();
		input(n);
		while(n--){
			input(a, b, d); a /= d, b /= d;
			if(a > b) swap(a, b);
			ans = 0;
			for(ri i = 1, r; i <= a; i = r + 1){
				r = min(a / (a / i), b / (b / i));
				ans += (s[r] - s[i-1]) * (a / i) * (b / i);
			}
			write(ans); puts("");
		}
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

