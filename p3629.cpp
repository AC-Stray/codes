#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
struct node{
    int v, w;
    node() {}
    node(int v, int w): v(v), w(w) {}
};
int n, k, fmx, mx, fnd, nd, res1, res2, f[100005], dis[100005];
vector<node> g[100005];
LL read(){
	ll n = 0; int f = 1; char ch = getchar();
	while('0' > ch || ch > '9'){
		if(ch == '-') f *= -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9'){
		n = (n << 1) + (n << 3) + ch-'0';
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
Void dfs(int now, int fa, int nw){
    f[now] = fa;
    if(nw > mx) mx = nw, nd = now;
    for(ri i = 0; i < g[now].size(); i++){
        int v = g[now][i].v;
        if(v == fa) continue;
        dfs(v, now, nw+g[now][i].w);
    }
}
Void dp(int now, int fa){
    for(int i = 0; i < g[now].size(); i++){
        int v = g[now][i].v;
        if(v == fa) continue;
        dp(v, now);
        mx = max(mx, dis[now] + dis[v] + g[now][i].w);
        dis[now] = max(dis[now], dis[v] + g[now][i].w);
    }
}
int main(){
    input(n, k);
    for(ri i = 1; i < n; i++){
        int u, v;
        input(u, v);
        g[u].push_back(node(v, 1));
        g[v].push_back(node(u, 1));
    }
    dfs(1, 0, 0);
    mx = 0;
    fnd = nd;
    dfs(nd, 0, 0);
    if(k == 1) return write(2*(n-1)-mx+1), 0;
    fmx = mx;
    while(fnd != 0){
        for(ri i = 0; i < g[fnd].size(); i++) if(g[fnd][i].v == f[fnd]) g[fnd][i].w = -1;
        for(ri i = 0; i < g[f[fnd]].size(); i++) if(g[f[fnd]][i].v == fnd) g[f[fnd]][i].w = -1;
        fnd = f[fnd];
    }
    while(nd != 0){
        for(ri i = 0; i < g[nd].size(); i++) if(g[nd][i].v == f[nd]) g[nd][i].w = -1;
        for(ri i = 0; i < g[f[nd]].size(); i++) if(g[f[nd]][i].v == nd) g[f[nd]][i].w = -1;
        nd = f[nd];
    }
    mx = -0x7fffffff;
    dp(1, 0);
    write(2*n-fmx-mx);
	return 0;
}