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
    const int N = 155;
    const int inf = 2e9;
    int n, m, ans, d[N], dst[N];
    struct edge{
        int u, v, d;
        edge() {}
        edge(int u, int v, int d): u(u), v(v), d(d) {}
    }edges[N];
    struct matrix{
        bitset<N> a[N];
        void unit(){
            for(int i = 0; i < n; i++) a[i].reset(), a[i].set(i);
        };
        void print(){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++) write(a[i][j]), putchar(' ');
                puts("");
            }
            puts("\n\n");
        }
        bitset<N>& operator [] (const int &index) { return a[index]; }
        const bitset<N> operator [] (const int &index) const { return a[index]; }
        matrix operator * (const matrix &b){
            matrix res;
            for(int i = 0; i < n; i++){
                for(int k = 0; k < n; k++){
                    if(a[i][k]) res[i] |= b[k];
                }
            }
            return res;
        }
    }a, g;
    matrix qpow(matrix n, int k){
        matrix res;
        res.unit();
        while(k > 0){
            if(k & 1) res = res * n;
            n = n * n;
            k >>= 1;
        }
        return res;
    }
    void Main(){
        input(n, m);
        for(int i = 0, u, v, d; i < m; i++){
            input(u, v, d);
            edges[i] = edge(u - 1, v - 1, d);
        }
        sort(edges, edges + m, [](edge a, edge b){
            return a.d < b.d;
        });
        a[0][0] = 1;
        ans = inf;
        for(int i = 0, p = 0; i < m; i++){
            int delta = edges[i].d - p;
            a = a * qpow(g, delta);
            g[edges[i].u][edges[i].v] = 1;
            queue<int> q;
            for(int j = 0; j < n; j++){
                if(a[0][j]) q.push(j), dst[j] = 0;
                else dst[j] = inf;
            }
            p = edges[i].d;
            while(!q.empty()){
                int u = q.front(); q.pop();
                for(int j = 0; j < n; j++){
                    if(!g[u][j] || dst[j] != inf) continue;
                    dst[j] = dst[u] + 1;
                    q.push(j);
                }
            }
            ans = min(ans, p + dst[n - 1]);
        }
        if(ans == inf) puts("Impossible");
        else write(ans);
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