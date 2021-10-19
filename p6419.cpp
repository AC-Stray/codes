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
const int N = 500005;
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
	ll dis[N], sdis[N], up[N], f[N], g[N], siz[N];
	struct node{
		int v, w;
		node() {}
		node(int v, int w): v(v), w(w) {}
	};
	vector<node> G[N];
	void dfs(int u, int fa){
		for(ri i = 0; i < G[u].size(); i++){
			node v = G[u][i];
			if(v.v == fa) continue;
			dfs(v.v, u);
			siz[u] += siz[v.v];
			if(siz[v.v]){
				f[u] += f[v.v] + 2 * v.w;
				if(dis[v.v] + v.w > dis[u]){
					sdis[u] = dis[u];
					dis[u] = dis[v.v] + v.w;
				}
				else if(dis[v.v] + v.w > sdis[u]) sdis[u] = dis[v.v] + v.w;
			}
		}
	}
	void dfs2(int u, int fa){
		for(ri i = 0; i < G[u].size(); i++){
			node v = G[u][i];
			if(v.v == fa) continue;
			if(k - siz[v.v]){
				g[v.v] = g[u] + f[u] - f[v.v];
				if(!siz[v.v]) g[v.v] += 2 * v.w;
				if(dis[v.v] + v.w == dis[u]) up[v.v] = max(up[u], sdis[u]) + v.w;
				else up[v.v] = max(up[u], dis[u]) + v.w;
			}
			dfs2(v.v, u);
		}
	}
	void Main(){
		input(n, k);
		for(ri i = 1, u, v, w; i < n; i++){
			input(u, v, w);
			G[u].emplace_back(v, w);
			G[v].emplace_back(u, w);
		}
		for(ri i = 0, u; i < k; i++) {
			input(u);
			siz[u] = 1;
		}
		dfs(1, 0);
		dfs2(1, 0);
		for(ri i = 1; i <= n; i++) write(f[i] + g[i] - max(dis[i], up[i])), puts("");
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
