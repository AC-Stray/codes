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
const int N = 5000005;
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
	int n, m, fa[N], d[N], p[N];
	ll ans;
	void treeToPrufer(){
		for(ri i = 1; i < n; i++) input(fa[i]), d[fa[i]]++;
		for(ri i = 1, j = 1; i <= n - 2; i++, j++){
			while(d[j]) j++;
			p[i] = fa[j];
			while(i <= n - 2 && !--d[p[i]] && p[i] < j) p[i+1] = fa[p[i]], i++;
		}
		for(ri i = 1; i <= n - 2; i++) ans ^= 1ll * i * p[i];
		write(ans);
	}
	void pruferToTree(){
		for(ri i = 1; i <= n - 2; i++) input(p[i]), d[p[i]]++; p[n-1] = n;
		for(ri i = 1, j = 1; i <= n - 1; i++, j++){
			while(d[j]) j++;
			fa[j] = p[i];
			while(i <= n - 1 && !--d[p[i]] && p[i] < j) fa[p[i]] = p[i+1], i++;
		}
		for(ri i = 1; i <= n - 1; i++) ans ^= 1ll * i * fa[i];
		write(ans);
	}
	void Main(){
		input(n, m);
		if(m == 1) treeToPrufer();
		else pruferToTree();
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

