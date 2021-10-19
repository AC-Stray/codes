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
const int N = 6005;
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
	int n, root, val[N], f[N][2];
	bool vis[N];
	vector<int> son[N];
	void dfs(int u){
		f[u][0] = 0;
		f[u][1] = val[u];
		for(ri i = 0; i < son[u].size(); i++){
			int v = son[u][i];
			dfs(v);
			f[u][0] += max(f[v][0], f[v][1]);
			f[u][1] += f[v][0];
		}
	}
	void Main(){
		input(n);
		for(ri i = 1; i <= n; i++) input(val[i]);
		for(ri i = 1, u, v; i < n; i++){
			input(u, v);
			son[v].push_back(u);
			vis[u] = true;
		}
		for(ri i = 1; i <= n; i++) if(!vis[i]) { root = i; break; }
		dfs(root);
		write(max(f[root][0], f[root][1]));
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

