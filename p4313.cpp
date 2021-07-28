#include<bits/stdc++.h>
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf = 0x3f3f3f3f;
const int N = 105;
const int M = 1e6 + 5;
int n, m, w, ans;
int s, t, ndcnt, egcnt, dis[M], val[M], start[M];
int mv1[] = {1, 0, -1, 0};
int mv2[] = {0, 1, 0, -1};
struct edge{
	int to, id;
	edge() {}
	edge(int to, int id): to(to), id(id) {}
};
vector<edge> g[M];
template<typename T>
inline T read() {
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
void input(Type& arg, Types&... args){
	arg = read<Type>();
	input(args...);
}
void addedge(int u, int v, int w){
	g[u].emplace_back(v, egcnt<<1);
	g[v].emplace_back(u, egcnt<<1|1);
	val[egcnt<<1] = w;
	val[egcnt<<1|1] = 0;
	egcnt++;
}
bool bfs(){
	memset(dis, 0, sizeof(dis));
	queue<int> q;
	q.push(s);
	dis[s] = 1;
	while(!q.empty()){
		int u = q.front(); q.pop();
		start[u] = 0;
		for(ri i = 0; i < g[u].size(); i++){
			edge v = g[u][i];
			if(!dis[v.to] && val[v.id]){
				dis[v.to] = dis[u] + 1;
				q.push(v.to);
			}
		}
	}
	return dis[t];
}
int dfs(int u, int in){
	if(u == t) return in;
	int out = 0;
	for(ri i = start[u]; i < g[u].size() && in - out > 0; i++){
		edge v = g[u][i];
		start[u] = i;
		if(val[v.id] && dis[v.to] == dis[u] + 1){
			int res = dfs(v.to, min(in - out, val[v.id]));
			out += res;
			val[v.id] -= res;
			val[v.id^1] += res;
		}
	}
	return out;
}
int dinic(){
	int tmp, res = 0;
	while(bfs()) while(tmp = dfs(s, inf)) res += tmp;
	return res;
}
Int id(int x, int y){
	return x * m + y + 2;
}
int main(){
	input(n, m);
	s = 0, t = 1, ndcnt = n * m + 1;
	for(ri i = 0; i < n; i++) for(ri j = 0; j < m; j++) input(w), ans += w, addedge(s, id(i, j), w);
	for(ri i = 0; i < n; i++) for(ri j = 0; j < m; j++) input(w), ans += w, addedge(id(i, j), t, w);
	for(ri i = 0; i < n; i++) for(ri j = 0; j < m; j++){
		input(w), ans += w, ndcnt++;
		addedge(s, ndcnt, w), addedge(ndcnt, id(i, j), inf);
		for(ri k = 0, ni, nj; k < 4; k++){
			ni = i + mv1[k], nj = j + mv2[k];
			if(ni < 0  || ni >= n || nj < 0 || nj >= m) continue;
			addedge(ndcnt, id(ni, nj), inf);
		}
	}
	for(ri i = 0; i < n; i++) for(ri j = 0; j < m; j++){
		input(w), ans += w, ndcnt++;
		addedge(ndcnt, t, w), addedge(id(i, j), ndcnt, inf);
		for(ri k = 0, ni, nj; k < 4; k++){
			ni = i + mv1[k], nj = j + mv2[k];
			if(ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
			addedge(id(ni, nj), ndcnt, inf);
		}
	}
	write(ans - dinic());
	return 0;
}

