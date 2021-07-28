#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 55;
const int M = 100005; 
ll n, k, s, t, cnt, start[M<<2], d[M<<2], val[M<<2];
bool dance[N][N];
char tmp;
struct edge{
    ll to, id;
    edge() {}
    edge(ll to, ll id): to(to), id(id) {}
};
vector<edge> g[N<<3];
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
bool bfs(){
    memset(d, 0, sizeof(d));
    d[s] = 1;
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        ll now = q.front(); q.pop();
        start[now] = 0;
        for(ri i = 0; i < g[now].size(); i++){
            edge v = g[now][i];
            if(!d[v.to] && val[v.id]){
                d[v.to] = d[now] + 1;
                q.push(v.to);
            }
        }
    }
    return d[t];
}
ll dfs(int p, ll in){
    if(p == t) return in;
    ll out = 0;
    for(ri i = start[p]; i < g[p].size(); i++){
        edge v = g[p][i];
        start[p] = i;
        if(val[v.id] && d[v.to] == d[p] + 1){
            ll res = dfs(v.to, min(val[v.id], in - out));
            if(!res) d[v.to] = 0;
            val[v.id] -= res;
            val[v.id^1] += res;
            out += res;
        }
    }
    return out;
}
ll dinic(){
    ll tmp, res = 0;
    while(bfs()){
        while(tmp = dfs(s, 1e18)){
           res += tmp;
        }
    }
    return res;
}
void add(int u, int v, int w){
	g[u].emplace_back(v, cnt<<1);
	g[v].emplace_back(u, cnt<<1|1);
	val[cnt<<1] = w;
	val[cnt<<1|1] = 0;
	cnt++;
}
void build(int mid){
	// cout << (n<<2)+2 << endl;
	for(ri i = 0; i < (n<<2) + 2; i++) g[i].clear();
	cnt = 0;
	s = 0, t = 1;
	for(ri i = 0; i < n; i++) add(s, (1+i)<<1, mid); //, cout << ((1+i)<<1) << ' ' << ((1+i)<<1|1) << endl;
	for(ri i = 0; i < n; i++) add((1+n+i)<<1, t, mid); //, cout << ((1+n+i)<<1) << ' ' << ((1+n+i)<<1|1) << endl;
	// cout << endl;
	for(ri i = 0; i < n; i++) add((1+i)<<1, (1+i)<<1|1, k);
	for(ri i = 0; i < n; i++) add((1+n+i)<<1|1, (1+n+i)<<1, k);
	for(ri i = 0; i < n; i++) for(ri j = 0; j < n; j++){
		if(dance[i][j]) add((1+i)<<1, (1+n+j)<<1, 1);
		else add((1+i)<<1|1, (1+n+j)<<1|1, 1);
	}
}
int main(){
	input(n, k);
	for(ri i = 0; i < n; i++){
		for(ri j = 0; j < n; j++){
			cin >> tmp;
			if(tmp == 'Y') dance[i][j] = true;
		}
	}
	int l = 0, r = n + k, ans;
	while(l <= r){
		int mid = (l + r) >> 1;
		build(mid);
		if(dinic() == mid * n) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
    write(ans);
    return 0;
}
