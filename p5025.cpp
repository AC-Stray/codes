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
const int MOD = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-10;
const int N = 500005;
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
	int L[N], R[N];
	ll n, ans, x[N], r[N], tl[N], tr[N];
	ll stk[N], top; 
	void Main(){
		input(n);
		for(ri i = 0; i < n; i++){
			input(x[i], r[i]);
			tl[i] = x[i] - r[i];
			tr[i] = x[i] + r[i];
			L[i] = R[i] = i;
		}
		for(ri i = 0; i < n; i++){
			while(top > 0 && tl[i] <= x[stk[top-1]]) L[i] = L[stk[--top]], tr[i] = max(tr[i], tr[stk[top]]);
			stk[top++] = i;
		}
		top = 0;
		for(ri i = n - 1; i >= 0; i--){
			while(top > 0 && tr[i] >= x[stk[top-1]]) R[i] = R[stk[--top]], L[i] = min(L[i], L[stk[top]]);
			stk[top++] = i;
		}
		for(ri i = 0; i < n; i++) ans = (ans + 1ll * (i + 1) * (R[i] - L[i] + 1) % MOD) % MOD;
		write(ans);
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

