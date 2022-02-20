#include<bits/stdc++.h>
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
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
void input(Type& arg, Types&... args){
    arg = read<Type>();
    input(args...);
}
namespace Main{
    const int N = 300005;
    const int inf = 0x3f3f3f3f;
    int n, q, cnt, fa[N<<1], pos[N<<1], dep[N<<1], st[N<<2][22], w[N<<2], ecnt;
    vector<int> g[N<<1];
    struct edge{
        int u, v, w;
        edge() {}
        edge(int u, int v, int w): u(u), v(v), w(w) {};
    };
    vector<edge> edges;
    bool pcmp(int x, int y){
        return pos[x] < pos[y];
    }
    struct segtree{
        struct segtree_node{
            int l, r, tag;
            int mnp, mxp, mn0, mx0;
            bool open;
        }t[N<<2];
        #define ls p<<1
        #define rs p<<1|1
        void pushup(int p){
            t[p].open = t[ls].open | t[rs].open;
            t[p].mnp = t[p].mxp = 0;
            if(t[ls].open){
                t[p].mnp = t[ls].mnp;
                t[p].mxp = t[ls].mxp;
            }
            if(t[rs].open){
                t[p].mnp = t[p].mnp != 0 ? min(t[ls].mnp, t[rs].mnp, pcmp) : t[rs].mnp;
                t[p].mxp = t[p].mxp != 0 ? max(t[ls].mxp, t[rs].mxp, pcmp) : t[rs].mxp;
            }
        }
        void pushtag(int p, int x){
            t[p].tag = x; t[p].open = x == 1;
            if(x == 1){
                t[p].mnp = t[p].mn0;
                t[p].mxp = t[p].mx0;
            }
        }
        void pushdown(int p){
            if(t[p].tag != 0){
                pushtag(ls, t[p].tag), pushtag(rs, t[p].tag);
                t[p].tag = 0;
            }
        }
        void build(int p, int l, int r){
            t[p].l = l, t[p].r = r;
            if(t[p].l == t[p].r){
                t[p].mnp = t[p].mxp = t[p].mn0 = t[p].mx0 = t[p].l;
                return;
            }
            int mid = l + r >> 1;
            build(ls, l, mid);
            build(rs, mid + 1, r);
            t[p].mn0 = min(t[ls].mn0, t[rs].mn0, pcmp);
            t[p].mx0 = max(t[ls].mx0, t[rs].mx0, pcmp);
            pushup(p);
        }
        void modify(int p, int l, int r, int k){
            if(t[p].l >= l && t[p].r <= r){
                pushtag(p, k);
                return;
            }
            int mid = t[p].l + t[p].r >> 1;
            pushdown(p);
            if(mid >= l) modify(ls, l, r, k);
            if(mid < r) modify(rs, l, r, k);
            pushup(p);
        }
        #undef ls
        #undef rs
    }tree;
    int get(int x){
        if(fa[x] == x) return x;
        return fa[x] = get(fa[x]);
    }
    void dfs(int u){
        st[++ecnt][0] = u, pos[u] = ecnt;
        for(int x: g[u]) dep[x] = dep[u] + 1, dfs(x), st[++ecnt][0] = u;
    }
    bool dcmp(int x, int y){
        return dep[x] < dep[y];
    }
    int lca(int u, int v){
        if(pos[v] < pos[u]) swap(u, v);
        int len = pos[v] - pos[u] + 1, lg = __lg(len);
        return min(st[pos[u]][lg], st[pos[v]-(1<<lg)+1][lg], dcmp);
    }
    void Main(){
        input(n, q);
        for(int i = 1, u, v, w; i < n; i++){
            input(u, v, w);
            edges.emplace_back(u, v, w);
        }
        sort(edges.begin(), edges.end(), [](edge a, edge b){
            return a.w < b.w;
        });
        for(int i = 1; i <= n << 1; i++) fa[i] = i;
        cnt = n;
        for(edge x: edges){
            int u = get(x.u), v = get(x.v);
            g[++cnt].push_back(u);
            g[cnt].push_back(v);
            w[cnt] = x.w;
            fa[u] = fa[v] = cnt;
        }
        dfs(cnt);
        for(int i = 1; i < 22; i++){
            for(int j = 1; j + (1 << i - 1) <= ecnt; j++){
                st[j][i] = min(st[j][i-1], st[j+(1<<i-1)][i-1], dcmp);
            }
        }
        tree.build(1, 1, n);
        while(q--){
            int op, x, y;
            input(op);
            if(op == 1){
                input(x, y);
                tree.modify(1, x, y, 1);
            }
            else if(op == 2){
                input(x, y);
                tree.modify(1, x, y, -1);
            }
            else{
                input(x);
                if(!tree.t[1].open) { puts("-1"); continue; }
                int a = tree.t[1].mnp, b = tree.t[1].mxp;
                if(a == x && b == x) puts("-1");
                else{
                    a = lca(a, x), b = lca(b, x);
                    write(dep[a] < dep[b] ? w[a] : w[b]);
                    puts("");
                }
            }
        }
        return;
    }
}
int main(){
    Main::Main();
    return 0;
}