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
const ll infll = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-10;
const int N = 200005;
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
	int n, m, q, cnt, r[N], c[N];
	bool vis[N<<1];
	vector<int> g[N<<1];
	void dfs(int u){
		vis[u] = true;
		for(ri i = 0; i < g[u].size(); i++){
			int v = g[u][i];
			if(!vis[v]) dfs(v);
		}
	}
	void Main(){
		input(n, m, q);
		for(ri i = 0; i < q; i++){
			input(r[i], c[i]);
			g[r[i]].push_back(n+c[i]);
			g[n+c[i]].push_back(r[i]);
		}
		for(ri i = 1; i <= n + m; i++) if(!vis[i]) dfs(i), cnt++;
		write(cnt-1);
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

