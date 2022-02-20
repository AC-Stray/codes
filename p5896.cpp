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
const int N = 100005;
const int M = 1000005;
#ifdef ONLINE_JUDGE
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++)
char buf[1000000], *p1(buf), *p2(buf);
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
	ll n, m, k, cnt;
	int q[N], head, tail;
	ll mid, f[N], g[N], c[N], ans;
	struct line{
		int l, r;
		line() {}
		line(ll l, ll r): l(l), r(r) {}
		bool operator < (const line &b) const { return l == b.l ? r > b.r : l < b.l; }
	}p[N];
//	ll square[M];
//	#define square(x) square[x]
	LL square(ll x) { return x * x; }
	LL X(int i) { return p[i+1].l; }
	LL Y(int i) { return f[i] + 1ll * p[i+1].l * (p[i+1].l - 2) - g[i]; }
	LL K(int i) { return 2 * p[i].r; }
	inline double slope(int p, int q) { return (double)(Y(p)-Y(q))/(X(p)-X(q)); }
	void dp(){
		head = tail = 1;
		c[1] = q[1] = 0;
		for(ri i = 1; i <= cnt; i++){
			while(head < tail && slope(q[head], q[head+1]) < K(i)) head++;
			f[i] = f[q[head]] + square(p[i].r - p[q[head]+1].l + 1) - g[q[head]] - mid;
			c[i] = c[q[head]] + 1;
			while(head < tail && slope(q[tail-1], q[tail]) >= slope(q[tail], i)) tail--;
			q[++tail] = i;
		}
	}
	void Main(){
		input(n, m, k);
//		for(ri i = 1; i <= m; i++) square[i] = 1ll * i * i;
		for(ri i = 1; i <= n; i++){
			input(p[i].l, p[i].r);
			if(p[i].l > p[i].r) swap(p[i].l, p[i].r);
		}
		sort(p + 1, p + n + 1);
		for(ri i = 1, mr = -1; i <= n; i++) if(p[i].r > mr) mr = p[i].r, p[++cnt] = p[i];
		for(ri i = 1; i < cnt; i++) if(p[i].r >= p[i+1].l) g[i] = square(p[i].r - p[i+1].l + 1);
		ll l = -1ll * m * m, r = 0;
		while(l <= r){
			mid = l + r >> 1;
			dp();
			if(c[cnt] <= k) ans = f[cnt] + mid * k, l = mid + 1;
			else r = mid - 1;
		}
		write(ans);
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

