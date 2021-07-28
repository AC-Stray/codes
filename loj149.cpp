#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define ri register int
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const double eps = 0.0000001;
const int MOD = 998244353;
const int N = 100005;
int n, k, a[N], b[N];
double c[N];
LL read(){
    ll n = 0; int f = 1; char ch = getchar();
    while('0' > ch || ch > '9'){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9'){
        n = (n << 1) + (n << 3) + ch - '0';
        ch = getchar();
    }
    return f * n;
}
Void write(ll x){
    if(x/10) write(x/10);
    putchar(x%10+'0');
}
Void input() {}
template<typename Type, typename... Types>
Void input(Type& arg, Types&... args){
    arg = read();
    input(args...);
}
bool check(double mid){
	double s = 0;
	for(ri i = 0; i < n; i++) c[i] = a[i] - mid * b[i];
	sort(c, c + n);
	for(ri i = n - 1; i >= n - k; i--) s += c[i];
	return s > 0;
}
signed main(){
	input(n, k);
	for(ri i = 0; i < n; i++) input(a[i]);
	for(ri i = 0; i < n; i++) input(b[i]);
	double l = 0, r = 1e5;
	while(r - l > eps){
		double mid = (l + r) / 2;
		if(check(mid)) l = mid;
		else r = mid;
	}
	printf("%.4lf", l);
    return 0;
}
