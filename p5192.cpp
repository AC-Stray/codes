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
    const int N = 1000005;
    const int M = 1000005;
    const int inf = 1e9;
    struct flow{
        int n, m, cnt, val[M<<1], start[N], d[N];
        struct edge{
            int v, id;
            edge() {}
            edge(int v, int id): v(v), id(id) {}
        };
        vector<edge> g[N];
        void init(){
            for(int i = 0; i < N; i++) g[i].clear();
            memset(val, 0, sizeof(val));
            cnt = 0;
        }
        void add(int u, int v, int w){
            // cerr << u << ' ' << v << ' ' << w << endl;
            cnt++;
            val[cnt<<1] = w;
            val[cnt<<1|1] = 0;
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
            while(bfs(s, t)) 
			res += dfs(s, t, inf);
            return res;
        }
    };
    struct bounded_flow: public flow{
        int tot, S, T, s, t, del, in[N], out[N];
        void init(){
            flow::init();
            memset(in, 0, sizeof(in));
            memset(out, 0, sizeof(out));
        }
        void add(int u, int v, int low, int upp){
            flow::add(u, v, upp - low);
            in[v] += low, out[u] += low;
        }
        void build(int _s, int _t, int _S, int _T, int c){
            tot = 0, s = _s, t = _t, S = _S, T = _T;
            flow::add(t, s, inf); del = cnt;
            for(int i = 0; i <= c; i++){
                if(in[i] > out[i]) flow::add(S, i, in[i] - out[i]), tot += in[i] - out[i];
                if(in[i] < out[i]) flow::add(i, T, out[i] - in[i]);
            }
        }
        int solve(){
            int tmp = dinic(S, T);
            // cerr << tmp << ' ' << tot;
            if(tmp != tot) return -1;
            int res = val[del<<1|1];
            // cerr << ' ' << res;
            val[del<<1] = val[del<<1|1] = 0;
            return res + dinic(s, t);
        }
    }f;
    int n, m, c, d, cnt, s, t, day;
    void Main(){
        while(cin >> n >> m){
            f.init(); s = 0, t = 1, cnt = m + 1;
            f.n = n, f.m = m;
            for(int i = 0, g; i < m; i++){
                input(g);
                f.add(i + 2, t, g, inf);
            }
            for(int i = 0; i < n; i++){
                input(c, d);
                day = ++cnt;
                f.add(s, day, 0, d);
                for(int j = 0, id, l, r; j < c; j++){
                    input(id, l, r);
                    f.add(day, id + 2, l, r);
                }
            }
            f.build(s, t, cnt + 1, cnt + 2, cnt);
            int ans = f.solve();
            printf("%d\n\n", ans);
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
