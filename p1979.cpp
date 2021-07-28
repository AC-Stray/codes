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
int mv1[] = {-1, 0, 1, 0};
int mv2[] = {0, 1, 0, -1};
int n, m, t, ex, ey, sx, sy, tx, ty, ans;
int tdis[35][35], dis[3610];
bool mp[35][35], vis[3610];
struct node{
    int v, w;
    node() {}
    node(int v, int w): v(v), w(w) {}
};
vector<node> g[3610];
struct pos{
    int x, y;
    pos() {}
    pos(int x, int y): x(x), y(y) {}
};
queue<pos> q;
queue<int> Q;
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
Int id(int x, int y){
    return (x*m + y) << 2;
}
Void bfs(int ex, int ey, int sx, int sy, int d){
    memset(tdis, 0x3f, sizeof(tdis));
    tdis[ex][ey] = 0;
    tdis[sx][sy] = 1;
    q.push(pos(ex, ey));
    while(!q.empty()){
        pos now = q.front(); q.pop();
        int nx = now.x, ny = now.y;
        for(ri i = 0; i < 4; i++){
            if(nx+mv1[i] < 0 || nx + mv1[i] >= n || ny + mv2[i] < 0 || ny + mv2[i] >= m) continue;
            if(mp[nx+mv1[i]][ny+mv2[i]] && tdis[nx+mv1[i]][ny+mv2[i]] == 0x3f3f3f3f){
                tdis[nx+mv1[i]][ny+mv2[i]] = tdis[nx][ny]+1;
                q.push(pos(nx+mv1[i], ny+mv2[i]));
            }
        }
    }
    if(d == -1) return;
    int tmp = id(sx, sy);
    for(ri i = 0; i < 4; i++){
        if(sx+mv1[i] < 0 || sx + mv1[i] >= n || sy + mv2[i] < 0 || sy + mv2[i] >= m) continue;
        if(tdis[sx+mv1[i]][sy+mv2[i]] != 0 && tdis[sx+mv1[i]][sy+mv2[i]] != 0x3f3f3f3f){
            g[tmp+d].push_back(node(tmp+i, tdis[sx+mv1[i]][sy+mv2[i]]));
            // cout << "Edge: " << tmp+d << " to " << tmp+i << " weight " << tdis[sx+mv1[i]][sy+mv2[i]] << endl;
        }
    }
    g[tmp+d].push_back(node(id(ex, ey) + (d+2)%4, 1));
    // cout << "Edge: " << tmp+d << " to " << id(ex, ey) + (d+2)%4 << " weight " << 1 << endl;
}
Void spfa(int sx, int sy){
    memset(dis, 0x3f, sizeof(dis));
    for(ri i = 0; i < 4; i++){
        int tx = sx + mv1[i], ty = sy + mv2[i];
        if(tdis[tx][ty] != 0x3f3f3f3f){
            dis[id(sx, sy)+i] = tdis[tx][ty];
            Q.push(id(sx, sy)+i);
        }
    }
    while(!Q.empty()){
        int now = Q.front(); Q.pop();
        vis[now] = false;
        for(ri i = 0; i < g[now].size(); i++){
            int v = g[now][i].v;
            if(dis[v] > dis[now] + g[now][i].w){
                dis[v] = dis[now] + g[now][i].w;
                if(!vis[v]) vis[v] = true, Q.push(v);
            }
        }
    }
}
int main(){
    // freopen("input.in", "r", stdin);
    input(n, m, t);
    for(ri i = 0; i < n; i++) for(ri j = 0; j < m; j++) input(mp[i][j]);
    for(ri i = 0; i < n; i++) for(ri j = 0; j < m; j++){
        if(mp[i][j]){
            if(i != 0 && mp[i-1][j]) bfs(i-1, j, i, j, 0);
            if(mp[i][j+1])           bfs(i, j+1, i, j, 1);
            if(mp[i+1][j])           bfs(i+1, j, i, j, 2);
            if(j != 0 && mp[i][j-1]) bfs(i, j-1, i, j, 3);
        }
    }
    while(t--){
        input(ex, ey, sx, sy, tx, ty);
        ex--, ey--, sx--, sy--, tx--, ty--;
        if(sx == tx && sy == ty){
            puts("0");
            continue;
        }
        bfs(ex, ey, sx, sy, -1);
        spfa(sx, sy);
        ans = 0x3f3f3f3f;
        for(ri i = 0; i < 4; i++) ans = min(ans, dis[id(tx, ty)+i]);
        if(ans == 0x3f3f3f3f) puts("-1");
        else write(ans), puts("");
    }
    return 0;
}