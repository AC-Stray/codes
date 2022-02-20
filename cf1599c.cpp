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
const double eps = 1e-7;
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
	int n;
	double p;
	double calc(double x){
		double x1 = x*(x-1)*(x-2)/6;
		double x2 = x*(x-1)*(n-x)/2;
		double x3 = x*(n-x)*(n-x-1)/4;
		double y  = (x1+x2+x3)/n/(n-1)/(n-2)*6;
		return y;
	}
	void Main(){
		cin >> n >> p;
	 	for(ri i = 0; i <= n; i++) if(calc(i) >= p - eps) return write(i);
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

