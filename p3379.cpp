#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<vector>
#include<set>
#include<queue>
#include<map>
#include<list>
#include<deque>
#include<cctype>
#include<climits>
#include<cmath>
#include<ctime>
#include<algorithm>
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
int n, m, s, fa[500005][25], depth[500005];
vector<int> g[500005];
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
Void dfs(int now, int father){
    fa[now][0] = father;
    depth[now] = depth[father]+1;
    for(ri i = 1; i <= ceil(log2(depth[now])); i++)
        fa[now][i] = fa[fa[now][i-1]][i-1];
    for(ri i = 0; i < g[now].size(); i++) if(g[now][i] != father) dfs(g[now][i], now);
}
Int LCA(int x, int y){
    if(depth[x] < depth[y]) swap(x, y);
    while(depth[x] > depth[y])
        x = fa[x][(int)ceil(log2(depth[x]-depth[y]+1))-1];
    if(x == y) return x;
    for(ri i = (int)ceil(log2(depth[x])) - 1; i >= 0; i--)
        if(fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}
int main(){
    n = read(), m = read(), s = read();
    for(ri i = 1; i < n; i++){
        int u = read(), v = read();
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(s, 0);
    while(m--){
        int a = read(), b = read();
        cout << LCA(a, b) << endl;
    }
	return 0;
}