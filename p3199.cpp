#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define ri register int
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const double eps = 0.000000001;
const int MOD = 998244353;
const int N = 3005;
int n, m, u, v;
double w, dis[N];
bool vis[N];
struct node{
	int v;
	double w;
	node() {}
	node(int v, double w): v(v), w(w) {}
};
vector<node> g[N];
LL read(){
    ll n = 0; int f = 1; char ch = getchar();
    while('0' > ch || ch > '9'){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9'){
        n = (n << 1) + (n << 3) + ch - '0';
        ch = getchar();
    }
    return f * n;
}
Void write(ll x){
    if(x/10) write(x/10);
    putchar(x%10+'0');
}
Void input() {}
template<typename Type, typename... Types>
Void input(Type& arg, Types&... args){
    arg = read();
    input(args...);
}
bool spfa(int p, double mid){
	vis[p] = true;
	for(ri i = 0; i < g[p].size(); i++){
		node v = g[p][i];
		if(dis[p] + v.w - mid < dis[v.v]){
			dis[v.v] = dis[p] + v.w - mid;
			if(vis[v.v] || spfa(v.v, mid)) return true;
		}
	}
	vis[p] = false;
	return false;
}
bool check(double mid){
	for(ri i = 1; i <= n; i++) dis[i] = 0;
	memset(vis, 0, sizeof(vis));
	for(ri i = 1; i <= n; i++) if(spfa(i, mid)) return true;
	return false;
}
signed main(){
	input(n, m);
	for(ri i = 0; i < m; i++){
		input(u, v);
		scanf("%lf",&w);
		g[u].emplace_back(v, w);
	}
	double l = -1e6, r = 1e6;
	while(r - l > eps){
		double mid = (l + r) / 2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	printf("%.8f", l);
    return 0;
}
