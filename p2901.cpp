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
int n, m, k, dst[1005];
bool vis[1005];
struct node{
    int v;
    ll w;
    node() {}
    node(int v, ll w): v(v), w(w) {}
    Bool operator < (const node &b) const {
        return w > b.w;
    }
};
vector<node> g[1005];
vector<node> G[1005];
priority_queue<node> q;
struct fastar{
    int v;
    ll dis;
    fastar() {}
    fastar(int v, ll dis): v(v), dis(dis) {}
    Bool operator < (const fastar &b) const {
        return dis + dst[v] > b.dis + dst[b.v];
    }
};
priority_queue<fastar> Q;
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
Void dijkstra(int s){
    for(ri i = 1; i <= n; i++) dst[i] = 0x7fffffff;
    dst[s] = 0;
    q.push(node(s, 0));
    while(!q.empty()){
        node now = q.top(); q.pop();
        if(vis[now.v]) continue;
        vis[now.v] = true;
        for(ri i = 0; i < G[now.v].size(); i++){
            node v = G[now.v][i];
            if(vis[v.v]) continue;
            if(dst[v.v] > dst[now.v] + v.w){
                dst[v.v] = dst[now.v] + v.w;
                q.push(node(v.v, dst[v.v]));
            }
        }
    }
}
Void Astar(){
    Q.push(fastar(n, 0));
    while(!Q.empty()){
        fastar now = Q.top(); Q.pop();
        if(now.v == 1){
            k--;
            write(now.dis); puts("");
            if(k == 0) exit(0);
            continue;
        }
        for(ri i = 0; i < g[now.v].size(); i++){
            node v = g[now.v][i];
            Q.push(fastar(v.v, now.dis+v.w));
        }
    }
}
int main(){
    input(n, m, k);
    for(ri i = 0; i < m; i++){
        int x, y, d;
        input(x, y, d);
        g[x].push_back(node(y, d));
        G[y].push_back(node(x, d));
    }
    dijkstra(1);
    Astar();
    while(k--) puts("-1");
    return 0;
}