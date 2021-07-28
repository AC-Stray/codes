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
int n, mxv, mxid, l, r, ans;
int marks[200005];
struct node{
    int v, w, id;
    node() {}
    node(int v, int w, int id): v(v), w(w), id(id) {}
};
vector<node> g[200005];
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
void dfs(int p, int fa, int step){
    if(step > mxv){
        mxv = step;
        mxid = p;
    }
    for(ri i = 0; i < g[p].size(); i++){
        node v = g[p][i];
        if(v.v == fa) continue;
        dfs(v.v, p, step + v.w);
    }
}
bool marking(int p, int fa, int to){
    if(p == to) return true;
    for(ri i = 0; i < g[p].size(); i++){
        node v = g[p][i];
        if(v.v == fa) continue;
        if(marking(v.v, p, to)){
            marks[v.id]++;
            return true;
        }
    }
}
signed main(){
    srand(time(0));
    const int timesLimit = 6;
    input(n);
    for(ri i = 1; i < n; i++){
        int u, v, w;
        input(u, v, w);
        g[u].push_back(node(v, w, i));
        g[v].push_back(node(u, w, i));
    }
    for(ri t = 0; t < timesLimit; t++){
        for(ri i = 1; i <= n; i++) random_shuffle(g[i].begin(), g[i].end());
        mxv = 0;
        dfs(1, 0, 0);
        l = mxid;
        mxv = 0;
        dfs(l, 0, 0);
        r = mxid;
        marking(l, 0, r);
    }
    for(ri i = 1; i < n; i++) if(marks[i] == timesLimit) ans++;
    cout << mxv << endl << ans;
    return 0;
}