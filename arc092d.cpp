#include<bits/stdc++.h>
#pragma GCC optimize("-Ofast")
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
    const int N = 1005;
    const int M = 200005;
    int n, m;
    bool can[N][N], vis[N], flag[M];
    vector<pair<int, int> > g[N], edges;
    void dfs(int s, int u){
        can[s][u] = true;
        for(pair<int, int> v: g[u]){
            if(can[s][v.first]) continue;
            dfs(s, v.first);
        }
    }
    void dfs2(int u){
        vis[u] = true;
        for(pair<int, int> v: g[u]){
            if(vis[v.first]) continue;
            dfs2(v.first);
        }
    }
    void Main(){
        input(n, m);
        for(int i = 0, u, v; i < m; i++){
            input(u, v);
            g[u].push_back(make_pair(v, i));
            edges.push_back(make_pair(u, v));
        }
        for(int i = 1; i <= n; i++) dfs(i, i);
        for(int i = 1; i <= n; i++){
            memset(vis, 0, sizeof(vis));
            vis[i] = true;
            for(pair<int, int> v: g[i]){
                if(vis[v.first]) { flag[v.second] = true; continue; }
                dfs2(v.first);
            }
            memset(vis, 0, sizeof(vis));
            vis[i] = true;
            for(int j = g[i].size() - 1; j >= 0; j--){
                pair<int, int> v = g[i][j];
                if(vis[v.first]) { flag[v.second] = true; continue; }
                dfs2(v.first);
            }
        }
        for(int i = 0; i < m; i++)
            puts(can[edges[i].second][edges[i].first] ^ flag[i] ? "diff" : "same");
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