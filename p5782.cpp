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
int n, m, x, y;
int low[2000005], dfn[2000005], dfnCnt, scc[2000005], sc, stk[2000005], top;
bool inStack[2000005];
vector<int> G[2000005];
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
void tarjan(int x){
    stk[top++] = x;
    inStack[x] = true;
    dfn[x] = low[x] = ++dfnCnt;
    for(ri i = 0; i < G[x].size(); i++){
        int v = G[x][i];
        if(!dfn[v]){
            tarjan(v);
            low[x] = min(low[x], low[v]);
        }
        else if(inStack[v]) low[x] = min(low[x], dfn[v]);
    }
    if(dfn[x] == low[x]){
        sc++;
        while(true){
            int tmp = stk[--top];
            inStack[tmp] = false;
            scc[tmp] = sc;
            if(tmp == x) break;
        }
    }
}
int main(){
    input(n, m);
    for(ri i = 0; i < m; i++){
        input(x, y);
        int X = x-1, Y = y-1;
        // G[X^1].push_back(Y);
        G[Y].push_back(X^1);
        // G[Y^1].push_back(X);
        G[X].push_back(Y^1);
    }
    for(ri i = 0; i < n<<1; i++) if(!dfn[i]) tarjan(i);
    // for(ri i = 0; i < n<<1; i++) cout << scc[i] << ' ';
    bool flag = true;
    for(ri i = 0; i < n; i++) if(scc[i<<1] == scc[(i<<1)+1]){
        flag = false;
        break;
    }
    if(flag) for(ri i = 0; i < n; i++) write(scc[i<<1] >= scc[(i<<1)+1] ? 2*i+2 : 2*i+1), puts("");
    else puts("NIE");
    return 0;
}