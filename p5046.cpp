#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int N = 100005;
const int S = 550;
#ifdef ONLINE_JUDGE
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,10000000,stdin),p1==p2)?EOF:*p1++)
char buf[10000000], *p1(buf), *p2(buf);
#endif
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
	int n, m, l, r, bL, bR, ans, a[N], c[N], cx, cy, x[S], y[S];
	int len, block, L[S], R[S], bel[N], pre[N], suf[N], f[S][S], cnt[S][N];
	struct node{
		int v, p;
		node() {}
		node(int v, int p): v(v), p(p) {}
		Bool operator < (const node &b) const { return v < b.v; };
	}b[N];
	struct bit{
		int v[N];
		Int lowbit(int x) { return x & -x; }
		Void add(int x, int k) { for(; x < N; x += lowbit(x)) v[x] += k; }
		Int query(int x) { int res = 0; for(; x; x ^= lowbit(x)) res += v[x]; return res; }
	}tree;
	int calc(int *a, int *b, int la, int lb){
		int ia = 1, ib = 1, ans = 0;
		while(ia <= la && ib <= lb){
			if(a[ia] < b[ib]) ia++;
			else ans += la - ia + 1, ib++;
		}
		return ans;
	}
	void init(){
		len = sqrt(n);
		block = (n+len-1) / len;
		for(ri i = 1; i <= n; i++) b[i] = node(a[i], i);
		for(ri i = 1; i <= block; i++){
			L[i] = R[i-1] + 1;
			R[i] = i * len;
		}
		R[block] = n;
		for(ri i = 1; i <= block; i++){
			for(ri j = L[i]; j <= R[i]; j++) bel[j] = i, cnt[i][a[j]]++;
			for(ri j = 2; j <= n; j++) cnt[i][j] += cnt[i][j-1];
			sort(b + L[i], b + R[i] + 1);
			for(ri j = L[i]; j <= R[i]; j++) c[j] = b[j].v;
			int tmp = 0;
			for(ri j = L[i]; j <= R[i]; j++){
				tree.add(a[j], 1);
				tmp += tree.query(n) - tree.query(a[j]);
				pre[j] = tmp;
			}
			f[i][i] = tmp;
			for(ri j = L[i]; j <= R[i]; j++){
				suf[j] = tmp;
				tree.add(a[j], -1);
				tmp -= tree.query(a[j]);
			}
		}
		for(ri i = 1; i <= n; i++){
			for(ri j = 1; j <= block; j++){
				cnt[j][i] += cnt[j-1][i];
			}
		}
		for(ri i = 1; i < block; i++){
			for(ri j = 1; j + i <= block; j++){
				int p = j, q = j + i;
				f[p][q] = f[p][q-1] + f[p+1][q] - f[p+1][q-1]
					+ calc(c+L[p]-1, c+L[q]-1, R[p]-L[p]+1, R[q]-L[q]+1);
			}
		}
	}
	void Main(){
		input(n, m);
		for(ri i = 1; i <= n; i++) input(a[i]);
		init();
		while(m--){
			input(l, r);
			#ifndef Liuxizai
			l ^= ans, r ^= ans;
			#endif
			bL = bel[l], bR = bel[r];
			ans = 0;
			if(bL == bR){
				cx = cy = 0;
				for(ri i = L[bL]; i <= R[bL]; i++){
					if(b[i].p < l) x[++cx] = b[i].v;
					else if(b[i].p <= r) y[++cy] = b[i].v;
				}
				ans = pre[r] - (l == L[bL] ? 0 : pre[l-1]) - calc(x, y, cx, cy);
			}
			else{
				cx = cy = 0;
				ans = suf[l] + pre[r] + f[bL+1][bR-1];
				for(ri i = L[bL]; i <= R[bL]; i++){
					if(b[i].p >= l){
						x[++cx] = b[i].v;
						if(bL+1<=bR-1) ans += cnt[bR-1][b[i].v-1] - cnt[bL][b[i].v-1];
					}
				}
				for(ri i = L[bR]; i <= R[bR]; i++){
					if(b[i].p <= r){
						y[++cy] = b[i].v;
						if(bL+1<=bR-1) ans += (R[bR-1]-L[bL+1]+1) - (cnt[bR-1][b[i].v]-cnt[bL][b[i].v]);
					}
				}
				ans += calc(x, y, cx, cy);
			}
			write(ans); puts("");
		}
		return;
	}
} // namespace
signed main(){
	#ifdef Liuxizai
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	#endif
	Main::Main();
	return 0;
}

