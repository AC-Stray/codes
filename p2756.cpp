#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
int m, n, u, v, ans, p[105];
bool vis[105];
vector<int> G[105];
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
Bool match(int x){
    for(ri i = 0; i < G[x].size(); i++){
        int v = G[x][i];
        if(!vis[v]){
            vis[v] = true;
            if(!p[v] || match(p[v])){
                p[v] = x;
                return true;
            }
        }
    }
    return false;
}
int main(){
    input(m, n);
    while(true){
        input(u, v);
        if(u == -1) break;
        G[u].push_back(v);
    }
    for(ri i = 1; i <= m; i++){
        memset(vis, 0, sizeof(vis));
        if(match(i)) ans++;
    }
    cout << ans << endl;
    for(ri i = 1; i <= n; i++) if(p[i]) cout << p[i] << ' ' << i << endl;
    return 0;
}