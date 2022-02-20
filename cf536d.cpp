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
    const int N = 2005;
    int n, m, s, t, cs, ct, a[N], num[N], sum[N][N];
    int dst[2][N], vis[N];
    bool ext[N][N];
    int rs[N][N], rt[N][N], f[2][N][N];
    struct node{
        int v, w;
        node() {}
        node(int v, int w): v(v), w(w) {}
        bool operator < (const node &b) const { return w > b.w; }
    };
    vector<node> g[N];
    void dijkstra(int s, int dst[], int &c){
        memset(dst, 0x3f, sizeof(vis));
        memset(vis, 0, sizeof(vis));
        dst[s] = 0;
        priority_queue<node> q;
        q.emplace(s, 0);
        while(!q.empty()){
            node u = q.top(); q.pop();
            if(vis[u.v]) continue;
            vis[u.v] = true;
            for(node v: g[u.v]){
                if(dst[v.v] > dst[u.v] + v.w){
                    dst[v.v] = dst[u.v] + v.w;
                    q.emplace(v.v, dst[v.v]);
                }
            }
        }
        memcpy(num, dst, sizeof(num));
        sort(num + 1, num + n + 1);
        c = unique(num + 1, num + n + 1) - num - 1;
        for(int i = 1; i <= n; i++) dst[i] = lower_bound(num + 1, num + c + 1, dst[i]) - num;
    }
    void Main(){
        input(n, m, s, t);
        for(int i = 1; i <= n; i++) input(a[i]);
        for(int i = 0, u, v, w; i < m; i++){
            input(u, v, w);
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        dijkstra(s, dst[0], cs);
        dijkstra(t, dst[1], ct);
        for(int i = 1; i <= n; i++){
            ext[dst[0][i]][dst[1][i]] = true;
            sum[dst[0][i]][dst[1][i]] += a[i];
        }
        for(int i = cs; i; i--){
            for(int j = ct; j; j--){
                sum[i][j] += sum[i][j+1] + sum[i+1][j] - sum[i+1][j+1];
            }
        }
        for(int i = 1; i <= cs; i++) rs[i][ct+1] = cs, rt[i][ct+1] = ct;
        for(int i = 1; i <= ct; i++) rs[cs+1][i] = cs, rt[cs+1][i] = ct;
        for(int i = cs; i; i--){
            for(int j = ct; j; j--){
                if(ext[i][j]) rs[i][j] = i, rt[i][j] = j;
                else{
                    rs[i][j] = min(rs[i+1][j], rs[i][j+1]);
                    rt[i][j] = min(rt[i+1][j], rt[i][j+1]);
                }
                f[0][i][j] = sum[i][j] - f[1][rs[i][j]+1][j];
                f[1][i][j] = sum[i][j] - f[0][i][rt[i][j]+1];
                if(i == 1 && j == 1) continue;
                f[0][i][j] = min(f[0][i][j], f[0][i][j+1]);
                f[1][i][j] = min(f[1][i][j], f[1][i+1][j]);
            }
        }
        int x = f[0][1][1], y = sum[1][1] - f[0][1][1];
        cerr << x << ' ' << y;
        if(x > y) puts("Break a heart");
        else if(x < y) puts("Cry");
        else puts("Flowers");
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
