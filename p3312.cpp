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
const int Q = 20005;
const int N = 100005;
const int _N = 100100;
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
	int q, cnt, pri[_N>>3], mu[_N], g[_N], ans[_N];
	pii f[_N];
	bool vis[_N];
	struct bit{
		int v[_N];
		Int lowbit(int x) { return x & -x; }
		Void add(int x, int k) { for(ri i = x; i <= N; i += lowbit(i)) v[i] += k; }
		Int query(int x) { int res = 0; for(ri i = x; i > 0; i -= lowbit(i)) res += v[i]; return res; }
	}tree;
	struct ask{
		int id, n, m, a;
		Bool operator < (const ask &b) const { return a < b.a; }
		int solve(){
			int res = 0;
			if(n > m) swap(n, m);
			for(ri i = 1, r; i <= n; i = r + 1){
				r = min(n / (n / i), m / (m / i));
				res += (tree.query(r) - tree.query(i - 1)) * (n / i) * (m / i);
			}
			return res;
		}
	}qs[Q];
	void init(){
		mu[1] = 1;
		f[1] = make_pair(1, 1);
		for(ri i = 2; i <= N; i++){
			if(!vis[i]){
				pri[cnt++] = i;
				mu[i] = -1;
				f[i] = make_pair(i + 1, i);
				g[i] = i + 1;
			}
			for(ri j = 0; j < cnt; j++){
				if(i * pri[j] > N) break;
				vis[i * pri[j]] = true;
				if(i % pri[j] == 0){
					g[i * pri[j]] = g[i] * pri[j] + 1;
					f[i * pri[j]] = make_pair(f[i].first / g[i] * g[i * pri[j]], i * pri[j]);
					break;
				}
				else{
					mu[i * pri[j]] = -mu[i];
					f[i * pri[j]] = make_pair(f[i].first * f[pri[j]].first, i * pri[j]);
					g[i * pri[j]] = pri[j] + 1;
				}
			}
		}
	}
	void Main(){
		init();
		sort(f, f + N);
		input(q);
		for(ri i = 0; i < q; i++){
			input(qs[i].n, qs[i].m, qs[i].a);
			qs[i].id = i;
		}
		sort(qs, qs + q);
		for(ri i = 0, p = 1; i < q; i++){
			while(f[p].first <= qs[i].a && p <= N){
				for(ri j = f[p].second; j <= N; j += f[p].second) tree.add(j, f[p].first*mu[j/f[p].second]);
				p++;
			}
			ans[qs[i].id] = qs[i].solve() & 0x7fffffff;
		}
		for(ri i = 0; i < q; i++) write(ans[i]), puts("");
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

