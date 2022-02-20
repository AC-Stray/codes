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
    const int N = 205;
    const int M = 30005;
    const int inf = 1e9;
    int n, m, tm, a[N][N], b[N][N];
    int s, t, cnt, c0, d[N], start[N], val[M], sav[M];
    struct edge{
        int v, id;
        edge() {}
        edge(int v, int id): v(v), id(id) {}
    };
    vector<edge> g[N];
    int add(int u, int v, int w){
        cnt++; val[cnt<<1] = w;
        g[u].push_back(edge(v, cnt<<1));
        g[v].push_back(edge(u, cnt<<1|1));
        return cnt;
    }
    bool bfs(){
        queue<int> q; q.push(s);
        memset(d, 0, sizeof(d));
        d[s] = 1;
        while(!q.empty()){
            int u = q.front(); q.pop();
            start[u] = 0;
            for(edge v: g[u]){
                if(d[v.v] || !val[v.id]) continue;
                d[v.v] = d[u] + 1;
                q.push(v.v);
            }
        }
        return d[t];
    }
    int dfs(int u, int in){
        if(u == t) return in;
        int out = 0;
        for(int i = start[u]; i < g[u].size() && out < in; i++){
            edge v = g[u][i];
            start[u] = i;
            if(val[v.id] && d[v.v] == d[u] + 1){
                int res = dfs(v.v, min(val[v.id], in - out));
                if(!res) d[v.v] = 0;
                val[v.id] -= res, val[v.id^1] += res;
                out += res;
            }
        }
        return out;
    }
    int dinic(){
        int res = 0;
        while(bfs()) res += dfs(s, inf);
        return res; 
    }
    void Main(){
        input(n, m);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                input(a[i][j]);
                int p = add(i, (a[i][j] - 1) / m + n, 1);
                sav[p<<1] = a[i][j];
            }
        }
        s = n << 1, t = n << 1 | 1;
        c0 = cnt;
        for(int i = 0; i < n; i++) add(s, i, 1);
        for(int i = n; i < n << 1; i++) add(i, t, 1);
        for(int i = 0; i < m; i++){
            dinic();
            for(int j = 0; j < n; j++){
                int match;
                for(edge v: g[j]){
                    if(!val[v.id^1]) continue;
                    val[v.id^1] = 0;
                    match = sav[v.id];
                    break;
                }
                b[i][j] = match;
            }
            for(int j = c0 + 1; j <= cnt; j++) swap(val[j<<1], val[j<<1|1]);
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++) write(b[j][i]), putchar(' ');
            puts("");
        }
        for(int i = 0; i < m; i++) sort(b[i], b[i] + n);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++) write(b[j][i]), putchar(' ');
            puts("");
        }
        cerr << (double)clock() / CLOCKS_PER_SEC;
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
