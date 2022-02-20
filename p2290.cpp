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
const int inf = 0x3f3f3f3f;
const int N = 155;
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
	int n, s, pri[N], cnt, a[N], d[N];
	ll ans = 1;
	bool vis[N];
	void init(){
		for(ri i = 2; i < N; i++){
			if(!vis[i]) pri[cnt++] = i;
			for(ri j = 0; j < cnt; j++){
				if(i * pri[j] >= N) break;
				vis[i * pri[j]] = true;
				if(i % pri[j] == 0) break;
			}
		}
	}
	void solve(int n, int modify){
		for(ri i = 0; i < cnt && n > 1; i++){
			while(n % pri[i] == 0){
				n /= pri[i];
				a[i] += modify;
			}
		}
	}
	void Main(){
		init();
		input(n);
		if(n == 1){
			input(d[0]);
			puts(d[0] ? "0" : "1");
			return;
		}
		for(ri i = 0; i < n; i++){
			input(d[i]);
			if(d[i] == 0) return puts("0"), void();
			s += d[i] - 1;
		}
		if(s != n - 2) return puts("0"), void();
		for(ri i = 2; i <= n - 2; i++) solve(i, 1);
		for(ri i = 0; i < n; i++) for(ri j = 2; j < d[i]; j++) solve(j, -1);
		for(ri i = 0; i < cnt; i++) while(a[i]--) ans *= pri[i];
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

