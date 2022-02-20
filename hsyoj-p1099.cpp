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
    const int N = 500005;
    int T, n, m, a[N], b[N], dep[N];
    char sc[N], tc[N];
    bool even, vis[N], sid[N], tid[N];
    vector<int> g[N];
    void dfs(int u, int fa){
        dep[u] = dep[fa] + 1;
        vis[u] = true;
        for(ri i = 0; i < g[u].size(); i++){
            int v = g[u][i];
            if(!vis[v]) dfs(v, u);
            else if((dep[u] + dep[v]) % 2 == 0) even = false;
        }
    }
    bool check(){
        for(ri i = 1; i <= n; i++){
            sid[i] = (sc[i] == 'R') ^ (dep[i] & 1);
            tid[i] = (tc[i] == 'R') ^ (dep[i] & 1);
        }
        if(even){
            cerr << "even\n";
            vector<int> s0, s1, t0, t1;
            for(ri i = 1; i <= n; i++){
                if(sid[i]) s1.push_back(a[i]);
                else       s0.push_back(a[i]);
                if(tid[i]) t1.push_back(b[i]);
                else       t0.push_back(b[i]);
            }
            if(s0.size() != t0.size()) return false;
            sort(s0.begin(), s0.end());
            sort(s1.begin(), s1.end());
            sort(t0.begin(), t0.end());
            sort(t1.begin(), t1.end());
            for(ri i = 0; i < s0.size(); i++) if(s0[i] != t0[i]) return false;
            for(ri i = 0; i < s1.size(); i++) if(s1[i] != t1[i]) return false;
            return true;
        }
        else{
            cerr << "odd\n";
            vector<int> s, t;
            int ssum = 0, tsum = 0;
            for(ri i = 1; i <= n; i++){
                s.push_back(a[i]);
                ssum ^= sid[i];
                t.push_back(b[i]);
                tsum ^= tid[i];
            }
            if(ssum != tsum) return false;
            sort(s.begin(), s.end());
            sort(t.begin(), t.end());
            for(ri i = 0; i < s.size(); i++) if(s[i] != t[i]) return false;
            return true;
        }
    }
    void Main(){
        input(T);
        while(T--){
            for(ri i = 1; i <= n; i++) g[i].clear();
            input(n, m);
            for(ri i = 0, u, v; i < m; i++){
                input(u, v);
                g[u].push_back(v);
                g[v].push_back(u);
            }
            for(ri i = 1; i <= n; i++) input(a[i]);
            scanf("%s", sc + 1);
            for(ri i = 1; i <= n; i++) input(b[i]);
            scanf("%s", tc + 1);
            even = true;
            memset(vis, 0, sizeof(vis));
            dfs(1, 0);
            puts(check() ? "YES" : "NO");
        }
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