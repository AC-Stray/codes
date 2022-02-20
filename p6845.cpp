#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri int
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
const int N = 100005;
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
    int dfnCnt, dep[N], dfn[N<<1], in[N], out[N];
    struct segtree{
        struct segtree_node{
            int l, r;
            int mn, mx, ltr, rtl, dia;
            int lazy;
        }t[N<<3];
        #define ls p<<1
        #define rs p<<1|1
        void pushup(int p){
            t[p].mx = max(t[ls].mx, t[rs].mx);
            t[p].mn = min(t[ls].mn, t[rs].mn);
            t[p].dia = max(t[ls].ltr + t[rs].mx, t[ls].mx + t[rs].rtl);
            t[p].dia = max(t[p].dia, max(t[ls].dia, t[rs].dia));
            t[p].ltr = max(t[ls].mx - 2 * t[rs].mn, max(t[ls].ltr, t[rs].ltr));
            t[p].rtl = max(t[rs].mx - 2 * t[ls].mn, max(t[ls].rtl, t[rs].rtl));
        }
        void update(int p, int v){
            t[p].mx += v, t[p].mn += v;
            t[p].ltr -= v, t[p].rtl -= v;
            t[p].lazy += v;
        }
        void pushdown(int p){
            if(!t[p].lazy) return;
            update(ls, t[p].lazy);
            update(rs, t[p].lazy);
            t[p].lazy = 0;
        }
        void build(int p, int l, int r){
            t[p].l = l, t[p].r = r;
            if(l == r){
                t[p].mx = t[p].mn = dep[dfn[l]];
                t[p].ltr = t[p].rtl = -dep[dfn[l]];
                return;
            }
            int mid = l + r >> 1;
            build(ls, l, mid);
            build(rs, mid + 1, r);
            pushup(p);
        }
        void modify(int p, int l, int r, int k){
            if(t[p].l >= l && t[p].r <= r){
                update(p, k);
                return;
            }
            int mid = t[p].l + t[p].r >> 1;
            pushdown(p);
            if(l <= mid) modify(ls, l, r, k);
            if(r > mid)  modify(rs, l, r, k);
            pushup(p);
        }
        #undef ls
        #undef rs
    }tree;
    int n, q, w, lastans;
    struct node{
        int v, w;
        node() {}
        node(int v, int w): v(v), w(w) {}
    };
    vector<node> g[N];
    struct edge{
        int u, v, w;
        edge() {}
        edge(int u, int v, int w): u(u), v(v), w(w) {}
    };
    vector<edge> edges;
    void dfs(int u, int fa){
        dfn[++dfnCnt] = u;
        in[u] = dfnCnt;
        for(ri i = 0; i < g[u].size(); i++){
            node v = g[u][i];
            if(v.v == fa) continue;
            dep[v.v] = dep[u] + v.w;
            dfs(v.v, u);
            dfn[++dfnCnt] = u;
        }
        out[u] = dfnCnt;
    }
    void Main(){
        input(n, q, w);
        for(ri i = 1, u, v, w; i < n; i++){
            input(u, v, w);
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
            edges.emplace_back(u, v, w);
        }
        dfs(1, 0);
        tree.build(1, 1, dfnCnt);
        // for(ri i = 1; i <= dfnCnt; i++) cerr << dfn[i] << ' '; cerr << endl;
        // cerr << tree.t[1].dia << endl;
        while(q--){
            int x, y;
            input(x, y);
            x = (x + lastans) % (n - 1);
            y = (y + lastans) % w;
            edge &now = edges[x];
            if(dep[now.u] > dep[now.v]) swap(now.u, now.v);
            cerr << x << ' ' << y << endl;
            tree.modify(1, in[now.v], out[now.v], y - now.w);
            now.w = y;
            write(lastans = tree.t[1].dia);
            puts("");
        }
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