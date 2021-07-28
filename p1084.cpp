#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
int n, m, ans = -1;
int army[50005], raCnt, ncCnt;
int fa[50005][20], dis[50005][20];
bool control[50005], used[50005];
struct node{
    int v, w;
    node() {}
    node(int v, int w): v(v), w(w) {}
    Bool operator < (const node &b) const { return w > b.w; }
}close[50005], restArmy[50005], noControl[50005];
vector<node> g[50005];
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
void dfs(int p, int f, int len){
    fa[p][0] = f;
    dis[p][0] = len;
    for(ri i = 1; i <= 17; i++){
        fa[p][i] = fa[fa[p][i-1]][i-1];
        dis[p][i] = dis[p][i-1] + dis[fa[p][i-1]][i-1];
    }
    for(auto x: g[p]){
        if(x.v == f) continue;
        dfs(x.v, p, x.w);
    }
}
bool allControlled(int p, int f){
    bool ok = true;
    if(control[p]) return true;
    else if(g[p].size() == 1) return false;
    for(auto x: g[p]){
        if(x.v == f) continue;
        if(!allControlled(x.v, p)){
            ok = false;
            if(p == 1){
                noControl[ncCnt].v = x.v;
                noControl[ncCnt++].w = x.w;
            }
            else return false;
        }
    }
    return ok;
}
Bool check(int tim){
    raCnt = ncCnt = 0;
    for(ri i = 1; i <= n; i++) control[i] = false, close[i].v = 0;
    for(ri i = 1; i <= m; i++) used[i] = false;
    for(ri i = 1; i <= m; i++){
        int p = army[i], way = 0;
        for(ri j = 17; j >= 0; j--){
            if(fa[p][j] > 1 && way + dis[p][j] <= tim){
                way += dis[p][j];
                p = fa[p][j];
            }
        }
        if(fa[p][0] == 1 && way + dis[p][0] <= tim){
            restArmy[raCnt].v = i;
            restArmy[raCnt++].w = tim - way - dis[p][0];
            if(!close[p].v || close[p].w > restArmy[raCnt-1].w){
                close[p].v = i;
                close[p].w = restArmy[raCnt-1].w;
            }
        }
        else control[p] = true;
    }
    if(allControlled(1, 0)) return true;
    sort(restArmy, restArmy + raCnt);
    sort(noControl, noControl + ncCnt);
    int now = 0;
    for(ri i = 0; i < ncCnt; i++){
        if(close[noControl[i].v].v && !used[close[noControl[i].v].v]){
            used[close[noControl[i].v].v] = true;
            continue;
        }
        while(now < raCnt && (used[restArmy[now].v] || restArmy[now].w < noControl[i].w)) now++;
        if(now == raCnt) return false;
        used[restArmy[now].v] = true;
    }
    return true;
}
signed main(){
    // freopen("P1084_5.in", "r", stdin);
    input(n);
    for(ri i = 1; i < n; i++){
        int u, v, w;
        input(u, v, w);
        g[u].push_back(node(v, w));
        g[v].push_back(node(u, w));
    }
    input(m);
    for(ri i = 1; i <= m; i++) input(army[i]);
    dfs(1, 0, 0);
    int l = 1, r = 500000;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(check(mid)) r = mid - 1, ans = mid;
        else l = mid + 1;
    }
    cout << ans;
    return 0;
}