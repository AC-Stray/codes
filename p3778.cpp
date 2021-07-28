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
const int inf = 0x3f3f3f3f;
const int N = 105;
const int K = 1005;
int n, m, kkk, b[N][K], s[N][K], g[N][N], income[N][K], f[N][N];
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
bool check(int mid){
	for(ri i = 1; i <= n; i++){
		for(ri j = 1; j <= n; j++){
			if(i == j) f[i][j] = -inf;
			else f[i][j] = income[i][j] - mid * g[i][j];
		}
	}
	for(ri k = 1; k <= n; k++)
		for(ri i = 1; i <= n; i++)
			for(ri j = 1; j <= n; j++)
				f[i][j] = max(f[i][j], f[i][k] + f[k][j]);
	for(ri i = 1; i <= n; i++) if(f[i][i] >= 0) return true;
	return false;
}
signed main(){
	input(n, m, kkk);
	for(ri i = 1; i <= n; i++){
		for(ri j = 1; j <= kkk; j++){
			input(b[i][j], s[i][j]);
			if(b[i][j] == -1) b[i][j] = inf;
			if(s[i][j] == -1) s[i][j] = 0;			
		}
	}
	for(ri i = 0, u, v, t; i < m; i++){
		input(u, v, t);
		g[u][v] = t;
	}
	for(ri i = 1; i <= n; i++)
		for(ri j = 1; j <= n; j++)
			if(!g[i][j]) g[i][j] = inf;
	for(ri k = 1; k <= n; k++)
		for(ri i = 1; i <= n; i++)
			for(ri j = 1; j <= n; j++)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	for(ri i = 1; i <= n; i++)
		for(ri j = 1; j <= n; j++)
			for(ri k = 1; k <= kkk; k++)
				income[i][j] = max(income[i][j], s[j][k] - b[i][k]);
	int l = 1, r = 1e9;
	while(r - l > 1){
		int mid = (l + r) >> 1;
		if(check(mid)) l = mid;
		else r = mid;
	}
	write(check(r) ? r : (check(l) ? l : l-1));
    return 0;
}
