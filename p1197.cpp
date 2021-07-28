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
const int N = 400005;
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
	int n, m, k, ans, fa[N];
	bool mark[N];
	vector<int> g[N], del, res;
	struct edge{
		int u, v;
		edge() {}
		edge(int u, int v): u(u), v(v) {}
	};
	vector<edge> edges;
	int get(int x){
		if(fa[x] == x) return x;
		return fa[x] = get(fa[x]);
	}
	void unite(int x, int y){
		fa[get(x)] = get(y);
	}
	void Main(){
		input(n, m);
		for(ri i = 0, x, y; i < m; i++){
			input(x, y);
			g[x].push_back(y);
			g[y].push_back(x);
			edges.push_back(edge(x, y));
		}
		input(k);
		for(ri i = 0, x; i < k; i++){
			input(x);
			del.push_back(x);
			mark[x] = true;
		}
		reverse(del.begin(), del.end());
		for(ri i = 0; i < n; i++) fa[i] = i;
		ans = n - k;
		for(ri i = 0; i < m; i++){
			if(!mark[edges[i].u] && !mark[edges[i].v] && get(edges[i].u) != get(edges[i].v)){
				unite(edges[i].u, edges[i].v);
				ans--;
			}
		}
		res.push_back(ans);
		for(ri i = 0; i < k; i++){
			int u = del[i];
			mark[u] = false;
			ans++;
			for(ri j = 0; j < g[u].size(); j++){
				int v = g[u][j];
				if(!mark[v] && get(u) != get(v)){
					unite(u, v);
					ans--;
				}
			}
			res.push_back(ans);
		}
		reverse(res.begin(), res.end());
		for(ri i = 0; i < res.size(); i++) write(res[i]), puts("");
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

