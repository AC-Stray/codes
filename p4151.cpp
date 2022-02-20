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
    const int N = 50005;
    const int L = 60;
    const int _L = 70;
    struct linearBasis{
        ll a[_L];
        void insert(ll x){
            for(ri i = L; i >= 0; i--){
                if(!(x >> i & 1)) continue;
                if(a[i]) x ^= a[i];
                else{
                    a[i] = x;
                    return;
                }
            }
        }
        ll queryMax(ll x){
            for(ri i = L; i >= 0; i--) if((x ^ a[i]) > x) x ^= a[i];
            return x;
        }
    }lb;
    int n, m;
    struct node{
        int v; ll w;
        node() {}
        node(int v, ll w): v(v), w(w) {}
    };
    vector<node> g[N];
    bool vis[N]; ll val[N];
    void dfs(int u, ll sum){
        vis[u] = true;
        val[u] = sum;
        for(ri i = 0; i < g[u].size(); i++){
            node v = g[u][i];
            if(!vis[v.v]) dfs(v.v, sum ^ v.w);
            else lb.insert(val[v.v] ^ val[u] ^ v.w);
        }
    }
    void Main(){
        input(n, m);
        for(ri i = 0; i < m; i++){
            int u, v; ll w;
            input(u, v, w);
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
        }
        dfs(1, 0);
        write(lb.queryMax(val[n]));
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