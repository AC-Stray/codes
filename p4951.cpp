#include<bits/stdc++.h>
#define ri /*register*/ int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int inf = 0x3f3f3f3f;
const int MOD = 998244353;
const int N = 100005;
const double eps = 1e-6;
#ifdef ONLINE_JUDGE
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
char buf[100000], *p1(buf), *p2(buf);
#endif
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
void input(Type& arg, Types&... args){
	arg = read<Type>();
	input(args...);
}
namespace Main{
	int n, m, f, u, v, c, t, fa[N];
	struct edge{
		int u, v, c, t;
		double cost;
		edge() {}
		edge(int u, int v, int c, int t): u(u), v(v), c(c), t(t) {}
		Void update(double mid) { cost = (ll)c + mid * t; }
		Bool operator < (const edge &b) const { return cost < b.cost; }
	};
	vector<edge> edges;
	Int get(int x){
		if(fa[x] == x) return x;
		return fa[x] = get(fa[x]);
	}
	Void unite(int x, int y){
		fa[get(x)] = get(y);
	}
	Bool check(double mid){
		for(edge &x: edges) x.update(mid);
		sort(edges.begin(), edges.end());
		for(ri i = 1; i <= n; i++) fa[i] = i;
		double tot = 0;
		for(ri i = 0; i < m; i++){
			if(get(edges[i].u) != get(edges[i].v)){
				unite(edges[i].u, edges[i].v);
				tot += edges[i].cost;
			}
		}
		return tot <= f;
	}
	void Main(){
		input(n, m, f);
		for(ri i = 0; i < m; i++){
			input(u, v, c, t);
			edges.emplace_back(u, v, c, t);
		}
		double l = 0, r = 1e9;
		while(r - l > eps){
			double mid = (l + r) / 2;
			if(check(mid)) l = mid;
			else r = mid;
		}
		printf("%.4f", l);
		return;
	}
}
int main(){
	Main::Main();
	return 0;
}
