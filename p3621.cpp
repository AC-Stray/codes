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
    int lc, rc;
}nodes[100005];
int n, mind, maxd, ans, rt;
bool flag;
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
Void dfs(int now, int step){
    if(nodes[now].lc == -1 || nodes[now].rc == -1) mind = min(mind, step), maxd = max(maxd, step);
    if(nodes[now].lc != -1) dfs(nodes[now].lc, step+1);
    if(nodes[now].rc != -1) dfs(nodes[now].rc, step+1);
}
Int solve(int now, int step){
    if(now == -1){
        if(step == mind) return 0;
        return 1;
    }
    int sl = solve(nodes[now].lc, step+1);
    int sr = solve(nodes[now].rc, step+1);
    if((sl == 0 && sr == 1) || (sl == 2 && sr == 1) || (sl == 0 && sr == 2)) ans++;
    if(sl == 2 || sr == 2){
        if(sl == 2 && sr == 2) flag = true;
        return 2;
    }
    if(sl + sr == 1) return 2;
    if(sl + sr == 0) return 0;
    return 1;
}
int main(){
    // freopen("23.in", "r", stdin);
    srand(rand());
    input(n);
    for(ri i = 1; i <= n; i++) input(nodes[i].lc, nodes[i].rc);
    mind = 0x3f3f3f3f;
    dfs(1, 1);
    // cout << maxd << ' ' << mind << endl;
    if(maxd - mind > 1){ puts("-1"); return 0; }
    else if(maxd == mind){ puts("0"); return 0; }
    solve(1, 0);
    if(flag){ puts("-1"); return 0; }
    else{ write(ans==4?ans+rand()%2:ans); puts(""); return 0; }
	return 0;
}