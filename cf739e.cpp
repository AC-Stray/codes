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
const double eps = 1e-10;
const int N = 2005;
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
	int n, a, b;
	double p[N], q[N], ul;
	pair<double, double> ans;
	struct node{
		double val;
		int pc, uc;
		node(): val(0), pc(0), uc(0) {}
		node(double val, int pc, int uc): val(val), pc(pc), uc(uc) {}
		node operator + (const node &b) { return node(val + b.val, pc + b.pc, uc + b.uc); }
		node operator + (const double &b) { return node(val + b, pc, uc); }
		node operator - (const double &b) { return node(val - b, pc, uc); }
		bool operator < (const node &b) const { return val + eps < b.val; }
	}dp[N], pCount(0, 1, 0), uCount(0, 0, 1);
	void solve(double pokeCost, double ultraCost){
		dp[0] = node();
		dp[0] = max(dp[0], pCount + p[0] - pokeCost);
		dp[0] = max(dp[0], uCount + q[0] - ultraCost);
		dp[0] = max(dp[0], pCount + uCount + p[0] + q[0] - p[0] * q[0] - pokeCost - ultraCost);
		for(ri i = 1; i < n; i++){
			dp[i] = dp[i-1];
			dp[i] = max(dp[i], dp[i-1] + pCount + p[i] - pokeCost);
			dp[i] = max(dp[i], dp[i-1] + uCount + q[i] - ultraCost);
			dp[i] = max(dp[i], dp[i-1] + pCount + uCount + p[i] + q[i] - p[i] * q[i] - pokeCost - ultraCost);
		}
	}
	double check(double pokeCost){
		double l = 0, r = 1, ans;
		while(r - l > eps){
			double mid = (l + r) / 2;
			solve(pokeCost, mid);
			if(dp[n-1].uc <= b) ans = r = mid;
			else l = mid;
		}
		solve(pokeCost, ans);
		return ans;
	}
	void Main(){
		input(n, a, b);
		for(ri i = 0; i < n; i++) scanf("%lf", p + i);
		for(ri i = 0; i < n; i++) scanf("%lf", q + i);
		check(0.01);
		double l = 0, r = 1;
		while(r - l > eps){
			double mid = (l + r) / 2;
			ul = check(mid);
			if(dp[n-1].pc <= a) r = mid, ans = make_pair(mid, ul);
			else l = mid;
		}
		solve(ans.first, ans.second);
		printf("%.12lf", dp[n-1].val + a * ans.first + b * ans.second);
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

