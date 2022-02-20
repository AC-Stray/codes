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
    const int N = 100005;
    int T, n, m, ans, sg[N], rt[N];
    bool vis[N];
    vector<int> g[N];
    struct trie{
        int cnt, ch[N*40][2], tag[N*40], siz[N*40];
        #define ls ch[x][0]
        #define rs ch[x][1]
        void request(int &x) { x = ++cnt, ls = rs = tag[x] = 0, siz[x] = 1; }
        void pushup(int x) { siz[x] = siz[ls] + siz[rs]; }
        void pushdown(int x, int d){
            if(!tag[x]) return;
            if(tag[x] >> d & 1) swap(ls, rs);
            tag[ls] ^= tag[x];
            tag[rs] ^= tag[x];
            tag[x] = 0;
        }
        void insert(int &x, int k, int d){
            if(!x) request(x);
            if(d == -1) return;
            pushdown(x, d);
            if(k >> d & 1) insert(rs, k, d - 1);
            else insert(ls, k, d - 1);
            pushup(x);
        }
        void merge(int &x, int y, int d){
            if(!x || !y) return x |= y, void();
            if(d == -1) return;
            pushdown(x, d), pushdown(y, d);
            merge(ls, ch[y][0], d - 1);
            merge(rs, ch[y][1], d - 1);
            pushup(x);
        }
        int mex(int x, int d){
            if(d == -1) return 0;
            pushdown(x, d);
            if(siz[ls] < (1 << d)) return mex(ls, d - 1);
            else return mex(rs, d - 1) | (1 << d);
        }
        #undef ls
        #undef rs
    }t;
    void dfs(int u, int fa){
        int sum = 0;
        vis[u] = true;
        for(ri i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if(v == fa) continue;
            dfs(v, u);
            sum ^= sg[v];
        }
        for(ri i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if(v == fa) continue;
            t.tag[rt[v]] ^= sum ^ sg[v];
            t.merge(rt[u], rt[v], 16);
        }
        t.insert(rt[u], sum, 16);
        sg[u] = t.mex(rt[u], 16);
    }
    void Main(){
        input(T);
        while(T--){
            for(ri i = 1; i <= n; i++) g[i].clear();
            memset(vis, 0, sizeof(vis));
            memset(rt, 0, sizeof(rt));
            t.cnt = 0;
            input(n, m);
            for(ri i = 0, u, v; i < m; i++){
                input(u, v);
                g[u].push_back(v);
                g[v].push_back(u);
            }
            ans = 0;
            for(ri i = 1; i <= n; i++) if(!vis[i]) dfs(i, 0), ans ^= sg[i];
            puts(ans ? "Alice" : "Bob");
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