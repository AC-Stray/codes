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
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int N = 200005;
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
    int n, m, deg[N], val[N], cal[N], p[N], cnt, sg[N];
    bool vis[N];
    vector<int> g[N];
    void topoSort(){
        queue<int> q;
        for(ri i = 1; i <= n; i++) if(!deg[i]) q.push(i);
        while(!q.empty()){
            int now = q.front(); q.pop();
            p[cnt++] = now;
            for(ri i = 0; i < g[now].size(); i++){
                int v = g[now][i];
                deg[v]--;
                if(!deg[v]) q.push(v);
            }
        }
    }
    void getSG(){
        for(ri i = 0; i < cnt; i++){
            for(ri j = 0; j < g[p[i]].size(); j++) vis[sg[g[p[i]][j]]] = true;
            while(vis[sg[p[i]]]) sg[p[i]]++;
            cal[sg[p[i]]] ^= val[p[i]];
            for(ri j = 0; j < g[p[i]].size(); j++) vis[sg[g[p[i]][j]]] = false;
        }
    }
    void Main(){
        input(n, m);
        for(ri i = 1; i <= n; i++) input(val[i]);
        for(ri i = 1, u, v; i <= m; i++){
            input(u, v);
            g[u].push_back(v);
            deg[v]++;
        }
        topoSort();
        reverse(p, p + cnt);
        // for(ri i = 0; i < cnt; i++) cerr << p[i] << ' '; cerr << endl;
        getSG();
        // for(ri i = 1; i <= n; i++) cerr << sg[i] << ' ';
        int s = -1;
        for(ri i = 0; i < n; i++) if(cal[i]) s = i;
        if(s == -1) return puts("LOSE"), void();
        puts("WIN");
        for(ri i = 1; i <= n; i++){
            if(sg[i] == s && (val[i] ^ cal[sg[i]]) < val[i]){
                val[i] ^= cal[sg[i]], cal[sg[i]] = 0;
                for(ri j = 0; j < g[i].size(); j++){
                    int v = g[i][j];
                    val[v] ^= cal[sg[v]];
                    cal[sg[v]] = 0;
                }
                break;
            }
        }
        for(ri i = 1; i <= n; i++) write(val[i]), putchar(' ');
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