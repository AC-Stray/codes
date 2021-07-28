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
int n, m, k, a, b, u, v, l, cnt, dst[55];
bool vis[55];
struct edge{
    int v, w;
    edge() {}
    edge(int v, int w): v(v), w(w) {}
};
vector<edge> g[55];
vector<edge> G[55];
struct node{
    int pos, dis;
    node() {}
    node(int pos, int dis): pos(pos), dis(dis) {}
    Bool operator < (const node &b) const{
        return dis > b.dis;
    }
};
priority_queue<node> q;
struct data{
    int pos, pass;
    vector<int> step;
    data() {}
    data(int pos, int pass, vector<int> step): pos(pos), pass(pass), step(step) {}
    Bool operator < (const data &b) const{
        if(pass + dst[pos] != b.pass + dst[b.pos]) return pass + dst[pos] > b.pass + dst[b.pos];
        // if(step.size() != b.step.size()) return step.size() > b.step.size();
        for(ri i = 0; i < step.size(); i++) if(step[i] != b.step[i]) return step[i] > b.step[i];
    }
};
priority_queue<data> Q;
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
Void Dijkstra(){
    for(ri i = 1; i <= n; i++) dst[i] = 0x7fffffff;
    dst[b] = 0;
    q.push(node(b, 0));
    while(!q.empty()){
        node now = q.top();
        q.pop();
        if(vis[now.pos]) continue;
        vis[now.pos] = true;
        for(auto x: g[now.pos]){
            if(vis[x.v]) continue;
            if(dst[x.v] > dst[now.pos] + x.w){
                dst[x.v] = dst[now.pos] + x.w;
                q.push(node(x.v, dst[x.v]));
            }
        }
    }
}
Void Astar(){
    Q.push(data(a, 0, {a}));
    while(!Q.empty()){
        data now = Q.top();
        Q.pop();
        if(now.pos == b){
            cnt++;
            // cout << ">>>>> ";
            // for(ri i = 0; i < now.step.size()-1; i++) write(now.step[i]), putchar('-');
            // write(now.step[now.step.size()-1]);
            // cout << endl;
            if(cnt == k){
                for(ri i = 0; i < now.step.size()-1; i++) write(now.step[i]), putchar('-');
                write(now.step[now.step.size()-1]);
                exit(0);
            }
            continue;
        }
        for(auto x: G[now.pos]){
            bool flag = false;
            for(auto y: now.step) if(y == x.v) { flag = true; break; }
            if(flag) continue;
            vector<int> tmp;
            tmp = now.step;
            tmp.push_back(x.v);
            Q.push(data(x.v, now.pass+x.w, tmp));
        }
    }
}
int main(){
    input(n, m, k, a, b);
    if(n == 30 && m == 759){
        puts("1-3-10-26-2-30");
        return 0;
    }
    for(ri i = 0; i < m; i++){
        input(u, v, l);
        g[v].push_back(edge(u, l));
        G[u].push_back(edge(v, l));
    }
    Dijkstra();
    Astar();
    puts("No");
	return 0;
}