#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
int t, n, m, u, v, l, a;
int Q, K, S, v0, p0, lastans;
int fa[400005], w[400005], dep[400005], ff[400005][20];
int dst[400005];
bool vis[200005];
struct edge{
    int u, v, w, h;
    Bool operator < (const edge &b) const { return h > b.h; }
}edges[400005];
struct node{
    int v, w, h;
    node() {}
    node(int v, int w, int h): v(v), w(w), h(h) {}
};
vector<node> g[200005];
struct node2{
    int v, w;
    node2() {}
    node2(int v, int w): v(v), w(w) {}
    Bool operator < (const node2 &b) const { return w > b.w; }
};
priority_queue<node2> q;
int cnt;
vector<int> tree[400005];
LL read(){
    ll n = 0; int f = 1; char ch = getchar();
    while('0' > ch || ch > '9'){
        if(ch == '-') f *= -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9'){
        n = (n << 1) + (n << 3) + ch-'0';
        ch = getchar();
    }
    return f * n;
}
Void write(ll x){
    if(x/10) write(x/10);
    putchar(x%10+'0');
}
Void input() {}
template<typename Type, typename... Types>
Void input(Type& arg, Types&... args){
    arg = read();
    input(args...);
}
Void dijkstra(){
    memset(vis, 0, sizeof(vis));
    dst[1] = 0;
    q.push(node2(1, 0));
    while(!q.empty()){
        node2 now = q.top(); q.pop();
        if(vis[now.v]) continue;
        vis[now.v] = true;
        for(ri i = 0; i < g[now.v].size(); i++){
            node vv = g[now.v][i];
            if(!vis[vv.v] && dst[now.v] + vv.w < dst[vv.v]){
                dst[vv.v] = dst[now.v] + vv.w;
                q.push(node2(vv.v, dst[vv.v]));
            }
        }
    }
}
Int get(int x){
    if(fa[x] == x) return x;
    else return fa[x] = get(fa[x]);
}
Void kruskal(){
    memset(w, 0, sizeof(w));
    sort(edges, edges+m);
    for(ri i = 1; i <= (n<<1); i++) fa[i] = i;
    cnt = n;
    for(ri i = 0; i < m; i++){
        if(get(edges[i].u) != get(edges[i].v)){
            w[++cnt] = edges[i].h;
            tree[cnt].push_back(get(edges[i].u));
            tree[cnt].push_back(get(edges[i].v));
            fa[get(edges[i].u)] = fa[get(edges[i].v)] = cnt;
        }
        if(cnt == (n << 1) - 1) break;
    }
}
int dfs(int now, int fa){
    dep[now] = dep[fa] + 1;
    ff[now][0] = fa;
    for(ri i = 1; i <= 19; i++) ff[now][i] = ff[ff[now][i-1]][i-1];
    if(tree[now].size() == 0) return dst[now];
    for(ri i = 0; i < tree[now].size(); i++) dst[now] = min(dst[now], dfs(tree[now][i], now));
    return dst[now];
}
int main(){
    input(t);
    while(t--){
        lastans = 0;
        for(ri i = 1; i <= n; i++) g[i].clear();
        for(ri i = 1; i <= (n<<1); i++) tree[i].clear();
        input(n, m);
        for(ri i = 0; i < m; i++){
            input(u, v, l, a);
            edges[i] = {u, v, l, a};
            g[u].push_back(node(v, l, a));
            g[v].push_back(node(u, l, a));
        }
        for(ri i = 1; i <= (n<<1); i++) dst[i] = 0x7fffffff;
        dijkstra();
        kruskal();
        dfs(cnt, 0);
        input(Q, K, S);
        while(Q--){
            input(v0, p0);
            v0 = (v0 + K * lastans - 1) % n + 1;
            p0 = (p0 + K * lastans) % (S + 1);
            for(ri i = 19; i >= 0; i--)
                if(dep[v0]-(1<<i) > 0 && w[ff[v0][i]] > p0) v0 = ff[v0][i];
            // cout << ">> " << v0 << ' ';
            write(lastans = dst[v0]);
            puts("");
        }
    }
    return 0;
}