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
	const int SEGTREE_SIZE = 10000005;
	struct segtreeNode{
		int ls, rs, l, r, sum, mx;
	};
	struct segtree{
		int tot, rt[N];
		segtreeNode t[SEGTREE_SIZE];
		#define ls t[p].ls
		#define rs t[p].rs
		void pushup(int p){
			t[p].sum = t[ls].sum + t[rs].sum;
			t[p].mx = max(t[ls].mx, t[rs].mx);
		}
		void change(int& p, int x, int l, int r, int k){
			if(!p) p = ++tot, t[p].l = l, t[p].r = r;
			if(l == r){
				t[p].sum = t[p].mx = k;
				return;
			}
			int mid = l + r >> 1;
			if(mid >= x) change(ls, x, l, mid, k);
			if(mid < x) change(rs, x, mid + 1, r, k);
			pushup(p);
		}
		int querySum(int p, int l, int r){
			if(!p) return 0;
			if(t[p].l >= l && t[p].r <= r) return t[p].sum;
			int res = 0, mid = t[p].l + t[p].r >> 1;
			if(mid >= l) res += querySum(ls, l, r);
			if(mid < r) res += querySum(rs, l, r);
			return res;
		}
		int queryMax(int p, int l, int r){
			if(!p) return 0;
			if(t[p].l >= l && t[p].r <= r) return t[p].mx;
			int res = -inf, mid = t[p].l + t[p].r >> 1;
			if(mid >= l) res = max(res, queryMax(ls, l, r));
			if(mid < r) res = max(res, queryMax(rs, l, r));
			return res;
		}
		#undef ls
		#undef rs
	}TREE;
	int n, q, level[N], belief[N];
	int dfnCnt, fa[N], dep[N], siz[N], son[N], top[N], dfn[N];
	string op;
	vector<int> g[N];
	void dfs1(int u, int f){
		son[u] = -1;
		siz[u] = 1;
		for(ri i = 0; i < g[u].size(); i++){
			int v = g[u][i];
			if(v == f) continue;
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dfs1(v, u);
			siz[u] += siz[v];
			if(son[u] == -1 || siz[v] > siz[son[u]]) son[u] = v;
		}
	}
	void dfs2(int u, int t){
		dfn[u] = ++dfnCnt;
		top[u] = t;
		if(son[u] == -1) return;
		dfs2(son[u], t);
		for(ri i = 0; i < g[u].size(); i++){
			int v = g[u][i];
			if(v == fa[u] || v == son[u]) continue;
			dfs2(v, v);
		}
	}
	int sumPath(int rt, int x, int y){
		int res = 0;
		while(x[top] != y[top]){
			if(x[top][dep] < y[top][dep]) swap(x, y);
			res += TREE.querySum(rt, x[top][dfn], x[dfn]);
			x = x[top][fa];
		}
		if(x[dfn] > y[dfn]) swap(x, y);
		res += TREE.querySum(rt, x[dfn], y[dfn]);
		return res;
	}
	int maxPath(int rt, int x, int y){
		int res = 0;
		while(x[top] != y[top]){
			if(x[top][dep] < y[top][dep]) swap(x, y);
			res = max(res, TREE.queryMax(rt, x[top][dfn], x[dfn]));
			x = x[top][fa];
		}
		if(x[dfn] > y[dfn]) swap(x, y);
		res = max(res, TREE.queryMax(rt, x[dfn], y[dfn]));
		return res;
	}
	void Main(){
		input(n, q);
		for(ri i = 1; i <= n; i++) input(level[i], belief[i]);
		for(ri i = 1, u, v; i < n; i++){
			input(u, v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		dfs1(1, 0);
		dfs2(1, 1);
		for(ri i = 1; i <= n; i++) TREE.change(TREE.rt[belief[i]], dfn[i], 1, n, level[i]);
		while(q--){
			int x, y;
			cin >> op;
			input(x, y);
			if(op == "CC"){
				TREE.change(TREE.rt[belief[x]], dfn[x], 1, n, 0);
				TREE.change(TREE.rt[y], dfn[x], 1, n, level[x]);
				belief[x] = y;
			}
			else if(op == "CW"){
				TREE.change(TREE.rt[belief[x]], dfn[x], 1, n, y);
				level[x] = y;
			}
			else if(op == "QS") write(sumPath(TREE.rt[belief[x]], x, y)), puts("");
			else write(maxPath(TREE.rt[belief[x]], x, y)), puts("");
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

