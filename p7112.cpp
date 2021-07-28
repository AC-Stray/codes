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
const int N = 605;
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
	int n, p;
	ll a[N][N];
	int gauss(){
		ll res = 1;
		for(ri i = 0; i < n; i++){
			for(ri j = i + 1; j < n; j++){
				if(a[j][i] > a[i][i]) swap(a[i], a[j]), res = p - res;
				while(a[j][i]){
					ll x = a[i][i] / a[j][i] % p;
					for(ri k = i; k < n; k++) a[i][k] = (a[i][k] - a[j][k] * x % p + p) % p;
					swap(a[i], a[j]);
					res = p - res;
				}
			}
		}
		for(ri i = 0; i < n; i++) res = res * a[i][i] % p;
		return res;
	}
	void Main(){
		input(n, p);
		for(ri i = 0; i < n; i++) for(ri j = 0; j < n; j++) a[i][j] = read<ll>() % p;
		cout << gauss();
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

