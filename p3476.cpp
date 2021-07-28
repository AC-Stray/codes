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
const ll infll = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-10;
const int N = 3005;
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
	int n, cnt, ans, xsum[N], ysum[N];
	struct point{
		int x, y;
		double angle;
		point() {}
		point(int x, int y): x(x), y(y) { angle = atan2(y, x); }
	}a[N], b[N];
	Bool cmpByXpos(point a, point b) { return a.x < b.x; }
	Bool cmpByAngle(point a, point b) { return a.angle < b.angle; }
	void Main(){
		input(n);
		for(ri i = 0; i < n; i++) input(a[i].x, a[i].y);
		sort(a, a + n, cmpByXpos);
		for(ri i = 0; i < n; i++){
			cnt = 0;
			for(ri j = i + 1; j < n; j++) b[cnt++] = point(a[j].x - a[i].x, a[j].y - a[i].y);
			sort(b, b + cnt, cmpByAngle);
			xsum[cnt] = ysum[cnt] = 0;
			for(ri j = cnt - 1; j >= 0; j--){
				xsum[j] = xsum[j+1] + b[j].x;
				ysum[j] = ysum[j+1] + b[j].y;
				ans += b[j].x * ysum[j+1] - b[j].y * xsum[j+1];
			}
		}
		cout << fixed << setprecision(1) << (long double)ans / 2.0;
		return;
	}
} // namespace
signed main(){
#ifdef Liuxizai
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif // Liuxizai
	Main::Main();
	return 0;
}

