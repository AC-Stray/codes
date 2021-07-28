#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<vector>
#include<set>
#include<queue>
#include<string>
#include<cstring>
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
int n, m, weight[10005], dfn[10005], low[10005], ans, dfnCnt, stack[10005], top = -1, u, v, scc[10005], sc, w[10005], memory[10005];
bool inStack[10005], vis[10005];
vector<int> g[10005];
vector<int> G[10005];
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
Void tarjan(int now){
    dfn[now] = low[now] = ++dfnCnt;
    stack[++top] = now; inStack[now] = true;
    for(auto x: g[now]){
        if(!dfn[x]){
            tarjan(x);
            low[now] = min(low[now], low[x]);
        }
        else if(inStack[x]){
            low[now] = min(low[now], dfn[x]);
        }
    }
    if(low[now] == dfn[now]){
        sc++;
        while(true){
            int tmp = stack[top];
            top--;
            inStack[tmp] = false;
            scc[tmp] = sc;
            w[sc] += weight[tmp];
            if(tmp == now) break;
        }
    }
}
Int dfs(int now){
    if(vis[now]) return memory[now];
    vis[now] = true;
    for(auto x: G[now])
        memory[now] = max(memory[now], dfs(x));
    memory[now] += w[now];
    return memory[now];
}
int main(){
    input(n, m);
    for(ri i = 1; i <= n; i++) input(weight[i]);
    for(ri i = 0; i < m; i++){
        input(u, v);
        g[u].push_back(v);
    }
    for(ri i = 1; i <= n; i++) if(!dfn[i]) tarjan(i);
    for(ri i = 1; i <= n; i++) for(auto x: g[i])
        if(scc[i] != scc[x]) G[scc[i]].push_back(scc[x]);
    for(ri i = 1; i <= sc; i++) if(!vis[i]) ans = max(ans, dfs(i));
    write(ans);
	return 0;
}