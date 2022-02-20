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
const int N = 5005;
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
	int len, fa[N], ans[N];
	ll a[N];
	bool vis[N];
	int get(int x){
		if(fa[x] == x) return x;
		return fa[x] = get(fa[x]);
	}
	void unite(int x, int y){
		fa[get(x)] = get(y);
	}
	void Main(){
		input(len);
		for(ri i = 0; i < len; i++) input(a[i]);
		for(ri i = 0; i < len; i++) fa[i] = i;
		for(ri i = 0; i < len; i++){
			for(ri j = i + 1; j < len; j++){
				ll tmp = sqrt(a[i] * a[j]);
				if(a[i] * a[j] > 0 && tmp * tmp == a[i] * a[j])
					unite(i, j);
			}
		}
		for(ri i = 0; i < len; i++){
			memset(vis, 0, sizeof(vis));
			int res = 0;
			for(ri j = i; j < len; j++){
				if(a[j] && !vis[get(j)]) vis[get(j)] = true, res++;
				ans[max(res, 1)]++;
			}
		}
		for(ri i = 1; i <= len; i++) write(ans[i]), putchar(' ');
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

