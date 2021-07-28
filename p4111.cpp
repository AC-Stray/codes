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
const int MOD = 1e9;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-10;
const int N = 105;
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
char chInput(){
	char ch = getchar();
	while(ch != '.' && ch != '*') ch = getchar();
	return ch;
}
namespace Main{
	int n, m, cnt, id[10][10];
	ll a[105][105];
	bool mp[10][10];
	void add(int u, int v){
		a[u][u]++, a[v][v]++, a[u][v]--, a[v][u]--;
	}
	int gauss(){
		ll res = 1;
		for(ri i = 0; i < cnt; i++){
			for(ri j = i + 1; j < cnt; j++){
				if(a[j][i] > a[i][i]) swap(a[i], a[j]), res = MOD - res;
				while(a[j][i]){
					ll x = a[i][i] / a[j][i];
					for(ri k = i; k < cnt; k++) a[i][k] = (a[i][k] - a[j][k] * x % MOD + MOD) % MOD;
					swap(a[i], a[j]);
					res = MOD - res;
				}
			}
		}
		for(ri i = 0; i < cnt; i++) res = (res * a[i][i] % MOD + MOD) % MOD;
		return res;
	}
	void Main(){
		input(n, m);
		for(ri i = 0; i < n; i++) for(ri j = 0; j < m; j++){
			if(chInput() == '.'){
				mp[i][j] = true;
				id[i][j] = cnt++; 
			}
		}
		for(ri i = 0; i < n; i++) for(ri j = 0; j < m; j++){
			if(!mp[i][j]) continue;
			if(mp[i+1][j]) add(id[i][j], id[i+1][j]);
			if(mp[i][j+1]) add(id[i][j], id[i][j+1]);
		}
		cnt--;
		write(gauss());
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

