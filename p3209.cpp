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
int t, n, m, eu[10005], ev[10005], id[205];
int dfn[20005], low[20005], dfnCnt, stk[20005], top, scc[20005], sc;
bool inStack[20005];
vector<int> g[20005];
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
    dfn[x] = low[x] = ++dfnCnt;
    stk[top++] = x;
    inStack[x] = true;
    for(ri i = 0; i < g[x].size(); i++){
        int v = g[x][i];
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
    input(t);
    while(t--){
        for(ri i = 0; i < m<<1; i++) g[i].clear();
        input(n, m);
        for(ri i = 0; i < m; i++) input(eu[i], ev[i]);
        for(ri i = 0; i < n; i++) id[read()] = i;
        if(m > 3 * n - 6){
            puts("NO");
            continue;
        }
        for(ri i = 0; i < m; i++){
            eu[i] = id[eu[i]];
            ev[i] = id[ev[i]];
            if(eu[i] > ev[i]) swap(eu[i], ev[i]);
        }
        // for(ri i = 0; i < m; i++) cout << eu[i] << ' ' << ev[i] << endl;
        for(ri i = 0; i < m - 1; i++) for(ri j = i + 1; j < m; j++){
            if(
                eu[i] < eu[j] && ev[i] > eu[j] && ev[i] < ev[j] || 
                eu[j] < eu[i] && ev[j] > eu[i] && ev[j] < ev[i]
            ){
                // cout << eu[i] << ' ' << ev[i] << "&&&&&&&&&" << endl;
                // cout << eu[j] << ' ' << ev[j] << "&&&&&&&&&" << endl;
                g[i<<1].push_back((j<<1)+1);
                g[(i<<1)+1].push_back(j<<1);
                g[j<<1].push_back((i<<1)+1);
                g[(j<<1)+1].push_back(i<<1);
            }
        }
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        memset(scc, 0, sizeof(scc));
        memset(inStack, 0, sizeof(inStack));
        dfnCnt = sc = top = 0;
        for(ri i = 0; i < m<<1; i++) if(!dfn[i]) tarjan(i);
        bool flag = true;
        for(ri i = 0; i < m; i++){
            if(scc[i<<1] == scc[(i<<1)+1]){
                flag = false;
                break;
            }
        }
        if(flag) puts("YES");
        else puts("NO");
    }
    return 0;
}
