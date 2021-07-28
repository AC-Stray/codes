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
const double eps = 1e-9;
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
	int n, pos[N<<1];
	bool covered[N];
	double ans;
	struct triangle{
		int x, y, m;
	}tri[N], t[N];
	int cnt;
	vector< pair<double, double> > p;
	unordered_map<double, double> memory;
	Bool cover(triangle a, triangle b){
		return min(b.x - a.x, b.y - a.y) >= 0 && max(b.x - a.x, b.y - a.y) <= b.m - a.m && b.y + b.m <= a.y + a.m && b.x + b.m <= a.x + a.m;
	}
	inline double f(double x){
		if(memory[x]) return memory[x];
		for(ri i = 0; i < cnt; i++){
			if(x >= t[i].x && x <= t[i].x + t[i].m){
				p.emplace_back(t[i].y, t[i].y + t[i].m - x + t[i].x);
			}
		}
		if(p.empty()) return 0.0;
		sort(p.begin(), p.end());
		double start = p[0].first, end = p[0].second, ans = 0.0;
		for(ri i = 1; i < p.size(); i++){
			if(p[i].first > end) ans += end - start, start = p[i].first, end = p[i].second;
			else end = max(end, p[i].second);
		}
		ans += end - start;
		p.clear();
		return memory[x] = ans;
	}
	inline double calc(double l, double r, double lv, double rv){
		return (r - l) * (lv + 4.0*f((l+r)*0.5) + rv) / 6.0;
	}
	double simpson(double l, double r, double ans, double lv, double rv){
		double mid = (l + r) * 0.5;
		double mv = f(mid);
		double left = calc(l, mid, lv, mv), right = calc(mid, r, mv, rv);
		if(fabs(left+right-ans) <= eps) return left + right;
		else return simpson(l, mid, left, lv, mv) + simpson(mid, r, right, mv, rv);
	}
	Bool cmp(triangle a, triangle b){
		return a.m > b.m;
	}
	void Main(){
		input(n);
		for(ri i = 0; i < n; i++) input(tri[i].x, tri[i].y, tri[i].m);
		sort(tri, tri + n, cmp);
		for(ri i = 0; i < n; i++){
			if(!covered[i]) t[cnt++] = tri[i];
			for(ri j = i + 1; j < n; j++) if(cover(tri[i], tri[j])) covered[j] = true;
		}
		for(ri i = 0; i < cnt; i++){
			pos[i<<1]   = t[i].x;
			pos[i<<1|1] = t[i].x + t[i].m;
		}
		sort(pos, pos + (cnt<<1));
		for(ri i = 1; i < (cnt<<1); i++){
			if(pos[i] == pos[i-1]) continue;
			double a = f(pos[i-1]+eps*2), b = f(pos[i]-eps*2);
			ans += simpson(pos[i-1]+eps*2, pos[i]-eps*2, calc(pos[i-1]+eps*2, pos[i]-eps*2, a, b), a, b);
		}
		printf("%.1lf", ans);
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


