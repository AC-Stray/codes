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
const int N = 505;
const int W = 1005;
int n, w, ans, wi[N], t[N];
double f[W];
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
	f[0] = 0;
	for(ri i = 1; i <= w; i++) f[i] = -1e9;
	for(ri i = 0; i < n; i++){
		for(ri j = w; j >= 0; j--){
			int p = min(w, j + wi[i]);
			f[p] = max(f[p], f[j] + t[i] - mid * wi[i]);
		}
	}
	return f[w] > 0;
}
signed main(){
	input(n, w);
	for(ri i = 0; i < n; i++) input(wi[i], t[i]);
	double l = 0, r = 1e5;
	while(r - l > eps){
		double mid = (l + r) / 2;
		if(check(mid)) l = mid;
		else r = mid;
	}
	ans = l * 1000;
	cout << ans;
    return 0;
}
