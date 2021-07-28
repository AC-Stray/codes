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
const int N = 20000005;
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
	int len1, len2, nxt[N], ext[N];
	ll ans;
	char a[N], b[N];
	void Main(){
		scanf("%s%s", a, b);
		len1 = strlen(a);
		len2 = strlen(b);
		nxt[0] = len2;
		for(ri i = 1, l = 0, r = 0; i < len2; i++){
			if(i <= r && nxt[i - l] < r - i + 1) nxt[i] = nxt[i - l];
			else{
				nxt[i] = max(0, r - i + 1);
				while(i + nxt[i] < len2 && b[i + nxt[i]] == b[nxt[i]]) nxt[i]++;
			}
			if(i + nxt[i] - 1 > r) l = i, r = i + nxt[i] - 1;
		}
		for(ri i = 0; i < len2; i++) ans ^= (ll)(i + 1) * (nxt[i] + 1);
		write(ans); puts("");
		while(ext[0] < len1 && a[ext[0]] == b[ext[0]]) ext[0]++;
		for(ri i = 1, l = 0, r = 0; i < len1; i++){
			if(i <= r && nxt[i - l] < r - i + 1) ext[i] = nxt[i - l];
			else{
				ext[i] = max(0, r - i + 1);
				while(i + ext[i] < len1 && a[i + ext[i]] == b[ext[i]]) ext[i]++;
			}
			if(i + ext[i] - 1 > r) l = i, r = i + ext[i] - 1;
		}
		ans = 0;
		for(ri i = 0; i < len1; i++) ans ^= (ll)(i + 1) * (ext[i] + 1);
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

