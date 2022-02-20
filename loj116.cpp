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
    const int M = 20005;
    const int inf = 1e9;
    struct flow{
        int n, m, cnt, val[M<<1], start[N], d[N];
        struct edge{
            int v, id;
            edge() {}
            edge(int v, int id): v(v), id(id) {}
        };
        vector<edge> g[N];
        void add(int u, int v, int w){
            cnt++;
            val[cnt<<1] = w;
            g[u].emplace_back(v, cnt<<1);
            g[v].emplace_back(u, cnt<<1|1);
        }
        bool bfs(int s, int t){
            memset(d, 0, sizeof(d));
            d[s] = 1;
            queue<int> q;
            q.push(s);
            while(!q.empty()){
                int u = q.front(); q.pop();
                start[u] = 0;
                for(edge v: g[u]){
                    if(!d[v.v] && val[v.id]){
                        d[v.v] = d[u] + 1;
                        q.push(v.v);
                    }
                }
            }
            return d[t];
        }
        int dfs(int u, int t, int in){
            if(u == t) return in;
            int out = 0;
            for(int i = start[u]; i < g[u].size() && in - out; i++){
                edge v = g[u][i];
                start[u] = i;
                if(val[v.id] && d[v.v] == d[u] + 1){
                    int res = dfs(v.v, t, min(in - out, val[v.id]));
                    if(!res) d[v.v] = 0;
                    out += res;
                    val[v.id] -= res;
                    val[v.id^1] += res;
                }
            }
            return out;
        }
        int dinic(int s, int t){
            int res = 0;
            while(bfs(s, t)) res += dfs(s, t, inf);
            return res;
        }
    }f;
    int s, t, S, T, tot, del, in[N], out[N];
    void Main(){
        input(f.n, f.m, s, t);
        for(int i = 0, u, v, low, upp; i < f.m; i++){
            input(u, v, low, upp);
            f.add(u, v, upp - low);
            in[v] += low; out[u] += low;
        }
        f.add(t, s, inf); del = f.cnt;
        S = f.n + 1, T = f.n + 2;
        for(int i = 1; i <= f.n; i++){
            if(in[i] > out[i]) f.add(S, i, in[i] - out[i]), tot += in[i] - out[i];
            if(in[i] < out[i]) f.add(i, T, out[i] - in[i]);
        }
        if(f.dinic(S, T) == tot){
            int tmp = f.val[del<<1|1];
            f.val[del<<1] = f.val[del<<1|1] = 0;
            write(tmp + f.dinic(s, t));
        }
        else puts("please go home to sleep");
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