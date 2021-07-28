#include<bits/stdc++.h>
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int MOD = 998244353;
const double eps = 1e-10;
double a;
template<typename T>
T read(){
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
inline double f(double x){
	return pow(x, a/x-x);
} 
inline double calc(double l, double r){
	return (r - l) * (f(l) + 4*f((l+r)/2) + f(r)) / 6;
}
double simpson(double l, double r, double ans){
	double mid = (l + r) / 2;
	double left = calc(l, mid), right = calc(mid, r);
	if(fabs(left + right - ans) < eps) return left + right;
	else return simpson(l, mid, left) + simpson(mid, r, right);
}
int main(){
	cin >> a;
	if(a < 0) puts("orz");
	else cout << fixed << setprecision(5) << simpson(eps, 15, calc(eps, 15));
	return 0;
}

