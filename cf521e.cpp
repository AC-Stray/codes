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
    const int N = 200005;
    int n, m, s, t, dep[N], d[N];
    bool flag, vis[N], sgn[N];
    vector<int> g[N], path, p0, ans[2];
    void dfs(int u, int fa){
        vis[u] = true;
        for(int v: g[u]){
            if(!vis[v]) dep[v] = dep[u] + 1, dfs(v, u);
            else if(v != fa && dep[u] > dep[v]) ++d[u], --d[v];
        }
    }
    void dfs3(int u, int fa){
        if(!ans[1].empty()) return;
        if(sgn[u]){
        	p0.push_back(u);
            if(dep[u] > dep[t]) t = u;
            ans[!ans[0].empty()] = p0;
            p0.pop_back();
            return;
        }
        if(vis[u]) return;
        vis[u] = true;
        p0.push_back(u);
        for(int v: g[u]) if(v != fa) dfs3(v, u);
        p0.pop_back();
    }
    void dfs2(int u, int fa){
        if(flag) return;
        vis[u] = sgn[u] = true;
        path.push_back(u);
        for(int v: g[u]){
        	if(!vis[v]){
	            dfs2(v, u);
	            if(flag) return;
	            d[u] += d[v];
			}
            if(d[u] >= 2){
            	flag = true, s = u;
                sgn[u] = false;
				memcpy(vis, sgn, sizeof(vis));
				dfs3(u, fa);
				return;
			}
        }
        sgn[u] = false;
        path.pop_back();
    }
    void Main(){
        input(n, m);
        for(int i = 0, u, v; i < m; i++){
            input(u, v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        dep[0] = -1;
        for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i, 0);
        memset(vis, 0, sizeof(vis));
        for(int i = 1; i <= n; i++) if(!vis[i]) dfs2(i, 0);
        if(ans[0].empty()) puts("NO");
        else{
            puts("YES");
            for(int i = 0; i < 2; i++){
                int p = 0;
                while(path[p] != *(ans[i].end()-1)) p++;
                while(path[p] != t) ans[i].push_back(path[++p]);
                write(ans[i].size()), putchar(' ');
                for(int x: ans[i]) write(x), putchar(' ');
                putchar('\n');
            }
            ans[0].clear();
            for(int i = path.size() - 1; i >= 0; i--){
                ans[0].push_back(path[i]);
                if(path[i] == t) break;
            }
            write(ans[0].size()), putchar(' ');
            for(int x: ans[0]) write(x), putchar(' ');
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
