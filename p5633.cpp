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
	int n, m, s, k, stot, mid, ans, cnt, res, fa[N];
	struct edge{
		int u, v, w;
		edge() {}
		edge(int u, int v, int w): u(u), v(v), w(w) {}
		Bool color() const { return u == s || v == s; }
		Int getval() const { return color() ? w - mid : w; }
		Bool operator < (const edge &b) const { return getval() == b.getval() ? color() > b.color() : getval() < b.getval(); }
	};
	vector<edge> edges;
	int get(int x){
		if(fa[x] == x) return x;
		return fa[x] = get(fa[x]);
	}
	void unite(int x, int y){
		fa[get(x)] = get(y);
	}
	void kruskal(){
		cnt = res = 0;
		for(ri i = 1; i <= n; i++) fa[i] = i;
		sort(edges.begin(), edges.end());
		for(ri i = 0; i < m; i++){
			if(get(edges[i].u) == get(edges[i].v)) continue;
			unite(edges[i].u, edges[i].v);
			cnt += edges[i].color();
			res += edges[i].getval();
		}
	}
	void Main(){
		input(n, m, s, k);
		for(ri i = 1; i <= n; i++) fa[i] = i;
		for(ri i = 0, u, v, w; i < m; i++){
			input(u, v, w);
			edges.emplace_back(u, v, w);
			stot += edges[i].color();
			unite(u, v);
		}
		if(stot < k) return puts("Impossible"), void();
		stot = 0;
		for(ri i = 1; i <= n; i++) stot += (fa[i] == i);
		if(stot != 1) return puts("Impossible"), void();
		ans = -inf;
		int l = -1e5, r = 1e5;
		mid = l; kruskal();
		if(cnt > k) return puts("Impossible"), void();
		mid = r; kruskal();
		if(cnt < k) return puts("Impossible"), void();
		while(l <= r){
			mid = l + r >> 1;
			kruskal();
			if(cnt <= k) ans = res + k * mid, l = mid + 1;
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

