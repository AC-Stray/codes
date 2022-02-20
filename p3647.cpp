#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int N = 200005;
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
    int n, ans, f[N][2], up[N][2];
    struct node{
        int v, w;
        node() {}
        node(int v, int w): v(v), w(w) {}
    };
    vector<node> g[N], son[N];
    vector<int> h[N][2];
    void dfs1(int u, int fa){
        for(ri i = 0; i < g[u].size(); i++){
            node v = g[u][i];
            if(v.v == fa) continue;
            son[u].push_back(v);
            dfs1(v.v, u);
        }
    }
    void dfs2(int u){
        int mx = -inf, smx = -inf;
        f[u][0] = 0;
        for(ri i = 0; i < son[u].size(); i++){
            int v = son[u][i].v, w = son[u][i].w;
            dfs2(v);
            f[u][0] += max(f[v][0], f[v][1] + w);
            int calc = f[v][0] + w - max(f[v][0], f[v][1] + w);
            if(calc > mx) smx = mx, mx = calc;
            else if(calc > smx) smx = calc;
        }
        f[u][1] = f[u][0] + mx;
        for(ri i = 0; i < son[u].size(); i++){
            int v = son[u][i].v, w = son[u][i].w;
            int calc = f[v][0] + w - max(f[v][0], f[v][1] + w);
            h[u][0].push_back(f[u][0] - max(f[v][0], f[v][1] + w));
            h[u][1].push_back(f[u][0] - max(f[v][0], f[v][1] + w));
            if(calc == mx) h[u][1][i] += smx;
            else h[u][1][i] += mx;
        }
    }
    void dp(int u){
        ans = max(ans, f[u][0] + up[u][0]);
        for(ri i = 0; i < son[u].size(); i++){
            int v = son[u][i].v, w = son[u][i].w;
            up[v][0] = max(up[u][0] + h[u][0][i], max(up[u][0] + h[u][1][i], up[u][1] + h[u][0][i]) + w);
            up[v][1] = up[u][0] + h[u][0][i] + w;
            dp(v);
        }
    }
    void Main(){
        input(n);
        for(ri i = 1, u, v, w; i < n; i++){
            input(u, v, w);
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        dfs1(1, 0);
        dfs2(1);
        up[1][1] = -inf, dp(1);
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