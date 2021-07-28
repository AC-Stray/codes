#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int MOD = 998244353;
const int inf = 0x7fffffff;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-10;
const int N = 1000005;
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
	int n, m, nval[N];
	const int SEGTREE_SIZE = N << 2;
	struct segtreeNode{
		int l, r, v, mx, mn;
		bool opposite;
	};
	struct segtree{
		segtreeNode t[N];
		#define ls p << 1
		#define rs p << 1 | 1
		void pushup(int p){
			t[p].v = t[ls].v + t[rs].v;
			t[p].mx = max(t[ls].mx, t[rs].mx);
			t[p].mn = min(t[ls].mn, t[rs].mn);
		}
		void pushdown(int p){
			if(t[p].opposite){
				t[ls].v *= -1;
				t[rs].v *= -1;
				t[ls].mn *= -1;
				t[rs].mn *= -1;
				t[ls].mx *= -1;
				t[rs].mx *= -1;
				swap(t[ls].mn, t[ls].mx);
				swap(t[rs].mn, t[rs].mx);
				t[ls].opposite ^= 1;
				t[rs].opposite ^= 1;
				t[p].opposite = false;
			}
		}
		void build(int p, int l, int r){
			t[p].l = l, t[p].r = r;
			if(l == r){
				t[p].v = t[p].mn = t[p].mx = nval[l];
				return;
			}
			int mid = l + r >> 1;
			build(ls, l, mid);
			build(rs, mid + 1, r);
			pushup(p);
		}
		void inverse(int p, int l, int r){
			if(t[p].l >= l && t[p].r <= r){
				t[p].v *= -1;
				t[p].mn *= -1;
				t[p].mx *= -1;
				swap(t[p].mn, t[p].mx);
				t[p].opposite ^= 1;
				return;
			}
			int mid = t[p].l + t[p].r >> 1;
			pushdown(p);
			if(mid >= l) inverse(ls, l, r);
			if(mid < r) inverse(rs, l, r);
			pushup(p);
		}
		void change(int p, int x, int k){
			if(t[p].l == t[p].r && t[p].l == x){
				t[p].v = t[p].mn = t[p].mx = k;
				return;
			}
			int mid = t[p].l + t[p].r >> 1;
			pushdown(p);
			if(mid >= x) change(ls, x, k);
			if(mid < x) change(rs, x, k);
			pushup(p);
		}
		int queryMx(int p, int l, int r){
			if(t[p].l >= l && t[p].r <= r) return t[p].mx;
			int res = -inf, mid = t[p].l + t[p].r >> 1;
			pushdown(p);
			if(mid >= l) res = max(res, queryMx(ls, l, r));
			if(mid < r) res = max(res, queryMx(rs, l, r));
			pushup(p);
			return res;
		}
		int queryMn(int p, int l, int r){
			if(t[p].l >= l && t[p].r <= r) return t[p].mn;
			int res = inf, mid = t[p].l + t[p].r >> 1;
			pushdown(p);
			if(mid >= l) res = min(res, queryMn(ls, l, r));
			if(mid < r) res = min(res, queryMn(rs, l, r));
			pushup(p);
			return res;
		}
		int querySum(int p, int l, int r){
			if(t[p].l >= l && t[p].r <= r) return t[p].v;
			int res = 0, mid = t[p].l + t[p].r >> 1;
			pushdown(p);
			if(mid >= l) res += querySum(ls, l, r);
			if(mid < r) res += querySum(rs, l, r);
			pushup(p);
			return res;
		}
		#undef ls
		#undef rs
	}TREE;
	int dfnCnt, iid[N], id[N], fa[N], dep[N], siz[N], son[N], top[N], dfn[N], val[N];
	string op;
	struct edge{
		int v, w, id;
		edge() {}
		edge(int v, int w, int id): v(v), w(w), id(id) {}
	};
	vector<edge> g[N];
	void dfs1(int u, int f){
		son[u] = -1;
		siz[u] = 1;
		for(ri i = 0; i < g[u].size(); i++){
			int v = g[u][i].v;
			if(v == f) continue;
			val[v] = g[u][i].w;
			id[v] = g[u][i].id;
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs1(v, u);
			siz[u] += siz[v];
			if(son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
		}
	} 
	void dfs2(int u, int t){
		top[u] = t;
		dfn[u] = ++dfnCnt;
		if(son[u] == -1) return;
		dfs2(son[u], t);
		for(ri i = 0; i < g[u].size(); i++){
			int v = g[u][i].v;
			if(v == fa[u] || v == son[u]) continue;
			dfs2(v, v);
		}
	}
	void inversePath(int x, int y){
		while(x[top] != y[top]){
			if(x[top][dep] < y[top][dep]) swap(x, y);
			TREE.inverse(1, x[top][dfn], x[dfn]);
			x = x[top][fa];
		}
		if(x[dfn] == y[dfn]) return;
		if(x[dfn] > y[dfn]) swap(x, y);
		TREE.inverse(1, x[dfn] + 1, y[dfn]);
	}
	int mxPath(int x, int y){
		int res = -inf;
		while(x[top] != y[top]){
			if(x[top][dep] < y[top][dep]) swap(x, y);
			res = max(res, TREE.queryMx(1, x[top][dfn], x[dfn]));
			x = x[top][fa];
		}
		if(x[dfn] == y[dfn]) return res;
		if(x[dfn] > y[dfn]) swap(x, y);
		res = max(res, TREE.queryMx(1, x[dfn] + 1, y[dfn]));
		return res;
	}
	int mnPath(int x, int y){
		int res = inf;
		while(x[top] != y[top]){
			if(x[top][dep] < y[top][dep]) swap(x, y);
			res = min(res, TREE.queryMn(1, x[top][dfn], x[dfn]));
			x = x[top][fa];
		}
		if(x[dfn] == y[dfn]) return res;
		if(x[dfn] > y[dfn]) swap(x, y);
		res = min(res, TREE.queryMn(1, x[dfn] + 1, y[dfn]));
		return res;
	}
	int sumPath(int x, int y){
		int res = 0;
		while(x[top] != y[top]){
			if(x[top][dep] < y[top][dep]) swap(x, y);
			res += TREE.querySum(1, x[top][dfn], x[dfn]);
			x = x[top][fa];
		}
		if(x[dfn] == y[dfn]) return res;
		if(x[dfn] > y[dfn]) swap(x, y);
		res += TREE.querySum(1, x[dfn] + 1, y[dfn]);
		return res;
	}
	void Main(){
		input(n);
		for(ri i = 1, u, v, w; i < n; i++){
			input(u, v, w);
			u++, v++;
			g[u].push_back(edge(v, w, i));
			g[v].push_back(edge(u, w, i));
		}
		dfs1(1, 0);
		dfs2(1, 1);
		for(ri i = 1; i <= n; i++) iid[id[i]] = i;
		for(ri i = 1; i <= n; i++) nval[dfn[i]] = val[i];
		TREE.build(1, 1, n);
		input(m);
		while(m--){
			int u, v;
			cin >> op;
			input(u, v);
			if(op == "C") TREE.change(1, u[iid][dfn], v);
			else if(op == "N") u++, v++, inversePath(u, v);
			else if(op == "SUM") u++, v++, cout << sumPath(u, v) << endl;
			else if(op == "MAX") u++, v++, cout << mxPath(u, v) << endl;
			else u++, v++, cout << mnPath(u, v) << endl;
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

