#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define int long long
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
    int n, tot, a[N], p[N], f[2][N];
    vector<int> g[N];
    void dfs(int u, int fa){
        for(ri i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if(v == fa) continue;
            dfs(v, u);
            f[0][u] += f[0][v];
        }
        int k = 0, s = 0;
        for(ri i = 0; i < g[u].size(); i++){
            if(g[u][i] == fa) continue;
            p[k++] = f[1][g[u][i]];
        }
        sort(p, p + k, greater<int>());
        for(ri i = 0; i < k; i++){
            p[i] = min(p[i], a[u]);
            s += p[i];
        }
        if(k){
            if(p[0] > s - p[0]){
                f[0][u] += (s - p[0]) * 2 + p[0] - (s - p[0]);
                f[1][u] = min(2 * a[u] - s, a[u]);
            }
            else{
                f[0][u] += min(a[u] * 2, s);
                f[1][u] = max(0ll, min(2 * a[u] - s, a[u]));
            }
        }
        else{
            f[0][u] = 0;
            f[1][u] = a[u];
        }
    }
    void Main(){
        input(n);
        for(ri i = 1; i <= n; i++) input(a[i]), tot += a[i];
        for(ri i = 1, u, v; i < n; i++){
            input(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, 0);
        write(tot - f[0][1]);
        return;
    }
} // namespace
signed main(){
#ifdef Liuxizai
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif // Liuxizai
    Main::Main();
    return 0;
}