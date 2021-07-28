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
	int n;
	double r;
	struct point{
		double x, y;
		point() {}
		point(double x, double y): x(x), y(y) {}
	}a[N], o;
	inline double dis(point a, point b){
		return sqrt((a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y));
	}
	inline pair<point, double> getCircle(point a, point b, point c){
		double a1 = 2 * (b.x - a.x), a2 = 2 * (c.x - a.x);
		double b1 = 2 * (b.y - a.y), b2 = 2 * (c.y - a.y);
		double c1 = b.x*b.x - a.x*a.x + b.y*b.y - a.y*a.y;
		double c2 = c.x*c.x - a.x*a.x + c.y*c.y - a.y*a.y;
		double x = (b1 * c2 - b2 * c1) / (b1 * a2 - b2 * a1);
		double y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
		double r = dis(a, point(x, y));
		return make_pair(point(x, y), r);
	}
	Bool inCircle(point a){
		return dis(a, o) <= r;
	}
	void Main(){
		input(n);
		for(ri i = 0; i < n; i++) cin >> a[i].x >> a[i].y;
		random_shuffle(a, a + n);
		for(ri i = 0; i < n; i++) if(!inCircle(a[i])){
			o = a[i];
			for(ri j = 0; j < i; j++) if(!inCircle(a[j])){
				o = point((a[i].x + a[j].x) / 2, (a[i].y + a[j].y) / 2);
				r = dis(o, a[j]);
				for(ri k = 0; k < j; k++) if(!inCircle(a[k])){
					pair<point, double> res = getCircle(a[i], a[j] ,a[k]);
					o = res.first;
					r = res.second;
				}
			}
		}
		cout << fixed << setprecision(2) << o.x << ' ' << o.y << ' ' << r;
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

