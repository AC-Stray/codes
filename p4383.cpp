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
const int N = 300005;
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
	int n, k;
	ll ans, l, r, mid;
	struct node{
		int v, w;
		node() {}
		node(int v, int w): v(v), w(w) {}
	};
	vector<node> g[N];
	struct value{
		ll v; int c;
		value() {}
		value(ll v, int c): v(v), c(c) {}
		value operator + (const value &b){
			return value(v + b.v, c + b.c);
		}
		value operator + (const ll &b){
			return value(v + b, c);
		}
		bool operator < (const value &b) const {
			return v == b.v ? c < b.c : v < b.v;
		}
	}f[N][3];
	void dfs(int u, int fa){
		f[u][0] = f[u][1] = f[u][2] = value(0, 0);
		f[u][2] = max(f[u][2], value(-mid, 1));
		for(ri i = 0; i < g[u].size(); i++){
			int v = g[u][i].v, w = g[u][i].w;
			if(v == fa) continue;
			dfs(v, u);
			f[u][2] = max(f[u][2], max(f[u][2] + f[v][0], f[u][1] + f[v][1] + w + value(-mid, 1)));
			f[u][1] = max(f[u][1], max(f[u][0] + f[v][1] + w, f[u][1] + f[v][0]));
			f[u][0] = max(f[u][0], f[u][0] + f[v][0]);
		}
		f[u][0] = max(f[u][0], max(f[u][1] + value(-mid, 1), f[u][2]));
	}
	void Main(){
		input(n, k); k++;
		for(ri i = 1, u, v, w; i < n; i++){
			input(u, v, w);
			g[u].emplace_back(v, w);
			g[v].emplace_back(u, w);
			r += abs(w);
		}
		l = -r;
		while(l <= r){
			mid = l + r >> 1;
			dfs(1, 0);
			if(f[1][0].c >= k) ans = f[1][0].v + mid * k, l = mid + 1;
			else r = mid - 1;
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

