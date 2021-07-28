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
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-10;
const int N = 100005;
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
	int n, m, r, P, a[N], b[N];
	const int SEGTREE_SIZE = N << 2;
	struct segtreeNode{
		int l, r;
		ll v, add;
	};
	struct segtree{
		segtreeNode t[SEGTREE_SIZE];
		#define ls p << 1
		#define rs p << 1 | 1
		void pushup(int p) { t[p].v = (t[ls].v + t[rs].v) % P; }
		void pushdown(int p){
			if(t[p].add){
				t[ls].v += (t[ls].r - t[ls].l + 1) * t[p].add;
				t[rs].v += (t[rs].r - t[rs].l + 1) * t[p].add;
				t[ls].add += t[p].add;
				t[rs].add += t[p].add;
				t[p].add = 0;
			}
		}
		void build(int p, int l, int r){
			t[p].l = l, t[p].r = r;
			if(l == r){
				t[p].v = b[l];
				return;
			}
			int mid = l + r >> 1;
			build(ls, l, mid);
			build(rs, mid + 1, r);
			pushup(p);
		}
		void add(int p, int l, int r, int k){
			if(t[p].l >= l && t[p].r <= r){
				t[p].add += k;
				t[p].v += (t[p].r - t[p].l + 1) * k;
				return;
			}
			int mid = t[p].l + t[p].r >> 1;
			pushdown(p);
			if(l <= mid) add(ls, l, r, k);
			if(r > mid) add(rs, l, r, k);
			pushup(p);
		}
		ll query(int p, int l, int r){
			if(t[p].l >= l && t[p].r <= r) return t[p].v;
			int mid = t[p].l + t[p].r >> 1; ll res = 0;
			pushdown(p);
			if(l <= mid) res = (res + query(ls, l, r)) % P;
			if(r > mid) res = (res + query(rs, l, r)) % P;
			return res;
		}
		#undef ls
		#undef rs
	}TREE;
	int dfnCnt, fa[N], dep[N], siz[N], son[N], top[N], dfn[N];
	vector<int> g[N];
	void dfs1(int u, int f){
		son[u] = -1;
		siz[u] = 1;
		for(ri i = 0; i < g[u].size(); i++){
			int v = g[u][i];
			if(v == f) continue;
			dep[v] = dep[u] + 1;
			fa[v] = u;
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
			int v = g[u][i];
			if(v == fa[u] || v == son[u]) continue;
			dfs2(v, v);
		}
	}
	void addPath(int x, int y, int k){
		while(x[top] != y[top]){
			if(x[top][dep] < y[top][dep]) swap(x, y);
			TREE.add(1, x[top][dfn], x[dfn], k);
			x = x[top][fa];
		}
		if(x[dfn] > y[dfn]) swap(x, y);
		TREE.add(1, x[dfn], y[dfn], k);
	}
	ll queryPath(int x, int y){
		ll res = 0;
		while(x[top] != y[top]){
			if(x[top][dep] < y[top][dep]) swap(x, y);
			res = (res + TREE.query(1, x[top][dfn], x[dfn])) % P;
			x = x[top][fa];
		}
		if(x[dfn] > y[dfn]) swap(x, y);
		res = (res + TREE.query(1, x[dfn], y[dfn])) % P;
		return res;
	}
	void Main(){
		input(n, m, r, P);
		for(ri i = 1; i <= n; i++) input(a[i]);
		for(ri i = 1, u, v; i < n; i++){
			input(u, v);
			g[u].push_back(v);
			g[v].push_back(u);
		} 
		dfs1(r, 0);
		dfs2(r, r);
		for(ri i = 1; i <= n; i++) b[dfn[i]] = a[i] % P;
		TREE.build(1, 1, n);
		while(m--){
			int op, x, y, z;
			input(op);
			switch(op){
				case 1: input(x, y, z); addPath(x, y, z); break;
				case 2: input(x, y); write(queryPath(x, y)); puts(""); break;
				case 3: input(x, z); TREE.add(1, x[dfn], x[dfn] + x[siz] - 1, z); break;
				case 4: input(x); write(TREE.query(1, x[dfn], x[dfn] + x[siz] - 1)); puts(""); break;
			}
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

