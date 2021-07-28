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
const int N = 2000005;
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
	ll n, cnt, pri[N], phi[N], ans;
	bool vis[N];
	void initPhi(){
		phi[1] = 1;
		for(ri i = 2; i <= n; i++){
			if(!vis[i]){
				pri[cnt++] = i;
				phi[i] = i - 1;
			}
			for(ri j = 0; j < cnt; j++){
				if((ll)i * pri[j] > n) break;
				vis[i * pri[j]] = true;
				if(i % pri[j]) phi[i * pri[j]] = phi[i] * phi[pri[j]];
				else{
					phi[i * pri[j]] = phi[i] * pri[j];
					break;
				}
			}
		}
	}
	void Main(){
		input(n);
		initPhi();
		for(ri i = 1; i <= n; i++) ans += (n / i) * (n / i) * phi[i];
		write((ans - n * (n + 1) / 2) / 2);
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

