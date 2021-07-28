#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define ri register int
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int n, m, s, p, ans, money[500005], weight[500005];
int dfnCnt, sc, dfn[500005], low[500005], stk[500005], id[500005], top;
bool inStack[500005], inQueue[500005];
vector<int> g[500005], bar;
vector<int> G[500005];
int dst[500005];
queue<int> q;
LL read(){
	int res = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9'){ res = res * 10 + ch-'0', ch = getchar(); }
	return res;
}
Void write(ll n){
	if(n >= 10) write(n/10);
	putchar(n%10+'0');
}
void tarjan(int now){
	stk[++top] = now;
	inStack[now] = true;
	low[now] = dfn[now] = ++dfnCnt;
	for(ri i = 0; i < g[now].size(); i++){
		int v = g[now][i];
		if(dfn[v] == 0){
			tarjan(v);
			low[now] = min(low[now], low[v]);
		}
		else if(inStack[v]) low[now] = min(low[now], dfn[v]);
	}
	if(dfn[now] == low[now]){
		sc++;
		while(stk[top+1] != now){
			inStack[stk[top]] = false;
			id[stk[top--]] = sc;
		}
	}
}
Void spfa(int start){
	for(ri i = 1; i <= sc; i++) dst[i] = 0x7fffffff;
    dst[start] = weight[start];
	q.push(start);
    inQueue[start] = true;
	while(!q.empty()){
		int now = q.front(); q.pop();
        inQueue[now] = false;
		for(ri i = 0; i < G[now].size(); i++){
			int v = G[now][i];
			if(dst[now] + weight[v] < dst[v]){
				dst[v] = dst[now] + weight[v];
				if(!inQueue[v]) q.push(v), inQueue[v] = true;
			}
		}
	}
}
int main(){
	// File("atm")
	n = read(), m = read();
	for(ri i = 0; i < m; i++){
		int u = read(), v = read();
		g[u].push_back(v);
	}
	for(ri i = 1; i <= n; i++) money[i] = read();
	s = read(), p = read();
	for(ri i = 0; i < p; i++) bar.push_back(read());
	tarjan(s);
    // for(ri i = 1; i <= n; i++) cout << id[i] << ' '; cout << endl;
	for(ri i = 1; i <= n; i++) weight[id[i]] -= money[i];
	for(ri i = 1; i <= n; i++) for(ri j = 0; j < g[i].size(); j++) if(id[i] != id[g[i][j]]) G[id[i]].push_back(id[g[i][j]]);
    // for(ri i = 1; i <= sc; i++){ cout << i << ": "; for(auto x: G[i]) cout << x << ' '; cout << endl; }
	spfa(id[s]);
	for(ri i = 0; i < bar.size(); i++) ans = max(ans, -1 * dst[id[bar[i]]]);
	write(ans);
	return 0;
}