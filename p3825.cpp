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
int n, m, d, x[100005], y[100005];
char hx[100005], hy[100005];
int dfn[100005], low[100005], dfnCnt, scc[100005], sc, stk[100005], top;
bool inStack[100005];
string S;
vector<int> G[100005];
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
Void tarjan(int x){
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
Int getid(int n, char c){
    if(c == 'a') return n<<1;
    if(c == 'c') return (n<<1)+1;
    if(S[n] == 'a') return n<<1;
    return (n<<1)+1;
}
Void dfs(int p){
    if(p == S.size()){
        memset(dfn, 0, sizeof(dfn));
        dfnCnt = top = sc = 0;
        for(ri i = 0; i < n<<1; i++) G[i].clear();
        for(ri i = 0; i < m; i++){
            if(S[x[i]] == hx[i]) continue;
            if(S[y[i]] == hy[i]) G[getid(x[i], hx[i])].push_back(getid(x[i], hx[i])^1);
            else{
                G[getid(x[i], hx[i])].push_back(getid(y[i], hy[i]));
                G[getid(y[i], hy[i])^1].push_back(getid(x[i], hx[i])^1);
            }
        }
        for(ri i = 0; i < n<<1; i++) if(!dfn[i]) tarjan(i);
        for(ri i = 0; i < n; i++) if(scc[i<<1] == scc[(i<<1)+1]) return;
        for(ri i = 0; i < n; i++){
            if(scc[i<<1] < scc[(i<<1)+1]){
                if(S[i] == 'b' || S[i] == 'c') putchar('A');
                else putchar('B');
            }
            else{
                if(S[i] == 'a' || S[i] == 'b') putchar('C');
                else putchar('B');
            }
        }
        exit(0);
    }
    if(S[p] == 'x'){
        S[p] = 'a';
        dfs(p+1);
        S[p] = 'b';
        dfs(p+1);
    }
    else dfs(p+1);
}
int main(){
    input(n, d);
    cin >> S;
    input(m);
    for(ri i = 0; i < m; i++){
        cin >> x[i] >> hx[i] >> y[i] >> hy[i];
        x[i]--, y[i]--;
        hx[i] = hx[i] - 'A' + 'a';
        hy[i] = hy[i] - 'A' + 'a';
    }
    dfs(0);
    puts("-1");
    return 0;
}