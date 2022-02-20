#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
template<typename T>
inline T read(){
    T n = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(isdigit(ch)){
        n = n * 10 + ch - '0';
        ch = getchar();
    }
    return f * n;
}
template<typename T>
void write(T n){
    if(n/10) write(n/10);
    putchar(n%10+'0');
}
void input() {}
template<typename Type, typename... Types>
void input(Type &arg, Types&... args){
    arg = read<Type>();
    input(args...);
}
namespace Main{
    const int N = 20005;
    int n, m, ans, dfnCnt, dfn[N], low[N];
    bool cut[N];
    vector<int> g[N];
    void tarjan(int u, int root){
        dfn[u] = low[u] = ++dfnCnt;
        int deg = 0;
        for(ri i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if(!dfn[v]){
                tarjan(v, root);
                low[u] = min(low[u], low[v]);
                if(u != root && dfn[u] <= low[v]) cut[u] = true;
                else if(u == root) deg++;
            }
            low[u] = min(low[u], dfn[v]);
        }
        if(u == root && deg >= 2) cut[u] = true;
    }
    void Main(){
        input(n, m);
        for(ri i = 0, u, v; i < m; i++){
            input(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for(ri i = 1; i <= n; i++) if(!dfn[i]) tarjan(i, i);
        for(ri i = 1; i <= n; i++) ans += cut[i];
        write(ans); puts("");
        for(ri i = 1; i <= n; i++) if(cut[i]) write(i), putchar(' ');
        return;
    }
} // namespace
int main(){
#ifdef Liuxizai
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif // Liuxizai
    Main::Main();
    return 0;
}