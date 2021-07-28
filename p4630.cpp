#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define ri register int
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 100005;
int n, m, ans;
int tot, siz[N<<1], w[N<<1], dfnCnt, dfn[N], low[N], top, stk[N];
int cnt;
vector<int> g[N];
vector<int> t[N<<1];
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
void tarjan(int p){
	dfn[p] = low[p] = ++dfnCnt;
	stk[top++] = p;
	tot++;
	for(ri i = 0; i < g[p].size(); i++){
		int v = g[p][i];
		if(!dfn[v]){
			tarjan(v);
			low[p] = min(low[p], low[v]);
			if(low[v] == dfn[p]){
				cnt++;
				int tmp = 0;
				while(tmp != v){
					tmp = stk[--top];
					t[tmp].push_back(cnt);
					t[cnt].push_back(tmp);
					w[cnt]++;
				}
				t[p].push_back(cnt);
				t[cnt].push_back(p);
				w[cnt]++;
			}
		}
		else low[p] = min(low[p], dfn[v]);
	}
}
void dfs(int p, int fa){
	if(p <= n) siz[p] = 1;
	for(ri i = 0; i < t[p].size(); i++){
		int v = t[p][i];
		if(v == fa) continue;
		dfs(v, p);
		ans += 2 * w[p] * siz[p] * siz[v];
		siz[p] += siz[v];
	}
	ans += 2 * w[p] * siz[p] * (tot - siz[p]);
}
signed main(){
	input(n, m);
	for(ri i = 0, u, v; i < m; i++){
		input(u, v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	cnt = n;
	for(ri i = 1; i <= n; i++) w[i] = -1;
	for(ri i = 1; i <= n; i++){
		if(!dfn[i]){
			tot = top = 0;
			tarjan(i);
			dfs(i, 0);
		}
	}
	write(ans);
    return 0;
}
