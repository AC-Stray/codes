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
const double pi = acos(-1);
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
	int n, cnt, ans;
	struct point{
		int x, y;
		double angle;
		point() {}
		point(int x, int y): x(x), y(y) { angle = atan2(y, x); }
		Void calc() { angle = atan2(y, x); }
	}a[N<<1]; 
	Bool cmp(point a, point b){
		return a.angle < b.angle;
	}
	void Main(){
		input(n);
		if(n < 3) puts("0");
		for(ri i = 0; i < n; i++) input(a[i].x, a[i].y), a[i].calc();
		sort(a, a + n, cmp);
		for(ri i = n; i < (n << 1); i++) a[i] = a[i - n], a[i].angle += 2 * pi;
		ans = n * (n - 1) * (n - 2) / 6;
		int p = 1;
		for(ri i = 0; i < n; i++){
			while(a[p].angle - a[i].angle < pi) p++, cnt++;
			if(cnt >= 2) ans -= cnt * (cnt - 1) / 2;
			cnt--;
		}
		write(ans);
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

