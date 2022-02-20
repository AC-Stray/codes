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
const int N = 1000005;
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
    int n, k, dfn, fa[N], l[N], r[N], dep[N];
    bool vis[N];
    vector<int> g[N], ans;
    struct bit{
        int v[N];
        int lowbit(int x) { return x & -x; }
        void add(int x, int k) { for(; x < N; x += lowbit(x)) v[x] += k; }
        int query(int x) { int res = 0; for(; x; x -= lowbit(x)) res += v[x]; return res; }
    }tree;
    void dfs(int u, int f){
        fa[u] = f;
        dep[u] = dep[f] + 1;
        l[u] = ++dfn;
        for(ri i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if(v == f) continue;
            dfs(v, u);
        }
        r[u] = dfn;
    }
    void Main(){
        input(n, k);
        for(ri i = 1, u, v; i < n; i++){
            input(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(n, 0);
        tree.add(l[n], 1), tree.add(r[n]+1, -1);
        vis[n] = true;
        k = n - k - 1;
        for(ri i = n - 1; i >= 1 && k; i--){
            if(vis[i] || dep[i] - tree.query(l[i]) > k) continue;
            int t = i;
            while(!vis[t]){
                vis[t] = true;
                tree.add(l[t], 1), tree.add(r[t]+1, -1);
                k--;
                t = fa[t];
            }
        }
        cerr << k << endl;
        for(ri i = 1; i <= n; i++) if(!vis[i]) write(i), putchar(' ');
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
