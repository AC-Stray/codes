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
    const int MOD = 1e9 + 7;
    const int N = 205;
    int n, inv, dep[N], fa[N][9];
    ll ans, f[N][N];
    vector<int> g[N];
    ll qpow(ll n, ll k){
        ll res = 1;
        while(k > 0){
            if(k & 1) res = res * n % MOD;
            n = n * n % MOD;
            k >>= 1;
        }
        return res;
    }
    void dfs(int u, int f){
        dep[u] = dep[f] + 1;
        fa[u][0] = f;
        for(ri i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if(v == f) continue;
            dfs(v, u);
        }
    }
    int lca(int u, int v){
        if(dep[u] < dep[v]) swap(u, v);
        while(dep[u] > dep[v]) u = fa[u][(int)log2(dep[u]-dep[v])];
        if(u == v) return u;
        for(ri i = 8; i >= 0; i--){
            if(fa[u][i] != fa[v][i]){
                u = fa[u][i], v = fa[v][i];
            }
        }
        return fa[u][0];
    }
    ll solve(int root){
        dfs(root, 0);
        for(ri i = 1; i < 9; i++){
            for(ri j = 1; j <= n; j++){
                fa[j][i] = fa[fa[j][i-1]][i-1];
            }
        }
        ll res = 0;
        for(ri i = 1; i <= n; i++){
            for(ri j = i + 1; j <= n; j++){
                int len = dep[lca(i, j)];
                res = (res + f[dep[i]-len][dep[j]-len]) % MOD;
            }
        }
        return res;
    }
    void Main(){
        inv = qpow(2, MOD - 2);
        input(n);
        for(ri i = 1, u, v; i < n; i++){
            input(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        for(ri i = 1; i <= n; i++) f[i][0] = 1;
        for(ri i = 1; i <= n; i++){
            for(ri j = 1; j <= n; j++){
                f[i][j] = (f[i-1][j] + f[i][j-1]) * inv % MOD;
            }
        }
        for(ri i = 1; i <= n; i++) ans = (ans + solve(i)) % MOD;
        ans = ans * qpow(n, MOD - 2) % MOD;
        write(ans);
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