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
    int n, k, a[N], dep[N], siz[N];
    ll ans;
    vector<int> g[N];
    void dfs(int u, int fa){
        dep[u] = dep[fa] + 1;
        siz[u] = 1;
        for(ri i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if(v == fa) continue;
            dfs(v, u);
            siz[u] += siz[v];
        }
    }
    void Main(){
        input(n, k);
        for(ri i = 1, u, v; i < n; i++){
            input(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dfs(1, 0);
        for(ri i = 1; i <= n; i++) a[i] = i;
        sort(a + 1, a + n + 1, [](int x, int y){
            return dep[x] - siz[x] > dep[y] - siz[y];
        });
        for(ri i = 1; i <= k; i++) ans += dep[a[i]] - siz[a[i]];
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