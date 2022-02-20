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
    const int N = 200005;
    int T, n, m, val[N];
    bool vis[2][N];
    vector<int> g[N], col[2];
    void dfs(int u, int fa, int c){
        col[c].push_back(u), vis[c][u] = true;
        for(ri i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if(v == fa) continue;
            dfs(v, u, c ^ 1);
        }
    }
    void Main(){
        input(T);
        while(T--){
            for(ri i = 1; i <= n; i++) g[i].clear();
            input(n);
            for(ri i = 1, u, v; i < n; i++){
                input(u, v);
                g[u].push_back(v);
                g[v].push_back(u);
            }
            col[0].clear(), col[1].clear();
            memset(vis, 0, sizeof(vis));
            dfs(1, 0, 0);
            m = col[0].size() < col[1].size() ? 0 : 1;
            for(ri i = col[m].size(), j = 0, t = i & -i; i; i -= t, t = i & -i){
                for(ri k = 0; k < t; k++) val[col[m][j+k]] = t | k;
                j += t;
            }
            for(ri i = 1, j = 1; i <= n; i++){
                if(vis[m][i]) continue;
                while(col[m].size() >> __lg(j) & 1) j <<= 1;
                val[i] = j++;
            }
            for(ri i = 1; i <= n; i++) write(val[i]), putchar(' ');
            puts("");
        }
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