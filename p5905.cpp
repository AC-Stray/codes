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
ll n, m, u, v, w, cnt[3005], dst[3005], G[3005][3005];
bool inQueue[3005], vis[3005];
struct node{
    int v, w;
    node() {}
    node(int v, int w): v(v), w(w) {}
    Bool operator < (const node &b) const{
        return w > b.w;
    }
};
vector<node> g[3005];
queue<ll> q;
priority_queue<node> Q;
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
Void SPFA(){
    memset(dst, 0x3f, sizeof(dst));
    dst[0] = 0;
    q.push(0);
    inQueue[0] = true;
    while(!q.empty()){
        ll now = q.front();
        q.pop();
        inQueue[now] = false;
        for(auto x: g[now]){
            if(dst[now] + x.w < dst[x.v]){
                dst[x.v] = dst[now] + x.w;
                if(!inQueue[x.v]){
                    q.push(x.v);
                    if(++cnt[x.v] > n){
                        puts("-1");
                        exit(0);
                    }
                    inQueue[x.v] = true;
                }
            }
        }
    }
}
Void Dijkstra(int s){
    memset(vis, 0, sizeof(vis));
    G[s][s] = 0;
    Q.push(node(s, 0));
    while(!Q.empty()){
        node now = Q.top();
        Q.pop();
        if(vis[now.v]) continue;
        vis[now.v] = true;
        for(auto x: g[now.v]){
            if(G[s][x.v] > G[s][now.v] + x.w){
                G[s][x.v] = G[s][now.v] + x.w;
                if(!vis[x.v]) Q.push(node(x.v, G[s][x.v]));
            } 
        }
    }
}
int main(){
    input(n, m);
    for(ri i = 0; i < m; i++){
        input(u, v, w);
        g[u].push_back(node(v, w));
    }
    for(ri i = 1; i <= n; i++) g[0].push_back(node(i, 0));
    SPFA(); 
    // for(ri i = 1; i <= n; i++) cout << dst[i] << ' ';
    // cout << endl;
    for(ri i = 1; i <= n; i++) for(auto &x: g[i]) x.w += dst[i] - dst[x.v];
    for(ri i = 1; i <= n; i++) for(ri j = 1; j <= n; j++) G[i][j] = 1000000000;
    for(ri i = 1; i <= n; i++) Dijkstra(i);
    // for(ri i = 1; i <= n; i++){
    //     for(ri j = 1; j <= n; j++) cout << G[i][j] << ' ';
    //     cout << endl;
    // }
    for(ri i = 1; i <= n; i++){
        ll ans = 0;
        for(ri j = 1; j <= n; j++){
            if(G[i][j] == 1000000000) ans += j * 1000000000ll;
            else ans += j * (G[i][j] + dst[j] - dst[i]);
        }
        cout << ans << endl;
    }
	return 0;
}