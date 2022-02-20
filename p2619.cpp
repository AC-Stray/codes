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
	int v, e, need, mid, cnt, ans, res, fa[N];
	struct edge{
		int u, v, w;
		bool color;
		edge() {}
		edge(int u, int v, int w, bool color): u(u), v(v), w(w), color(color) {}
		Int get() const { return color ? w : w - mid; }
		bool operator < (const edge &b) const { return get() == b.get() ? color < b.color : get() < b.get(); }
	};
	vector<edge> edges;
	int getfa(int x){
		if(fa[x] == x) return x;
		return fa[x] = getfa(fa[x]);
	}
	void unite(int x, int y){
		fa[getfa(x)] = getfa(y);
	}
	void kruskal(){
		ans = cnt = 0;
		for(ri i = 0; i < v; i++) fa[i] = i;
		sort(edges.begin(), edges.end());
		for(ri i = 0; i < e; i++){
			if(getfa(edges[i].u) == getfa(edges[i].v)) continue;
			unite(edges[i].u, edges[i].v);
			ans += edges[i].get();
			cnt += !edges[i].color;
		}
	}
	void Main(){
		input(v, e, need);
		for(ri i = 0, u, v, w, c; i < e; i++){
			input(u, v, w, c);
			edges.emplace_back(u, v, w, c);
		}
		int l = -100, r = 100;
		while(l <= r){
			mid = l + r >> 1;
			kruskal();
			if(cnt >= need) res = ans + mid * need, r = mid - 1;
			else l = mid + 1;
		}
		write(res);
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

