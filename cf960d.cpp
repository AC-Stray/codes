#include<bits/stdc++.h>
#define ri /*register*/ int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int inf = 0x3f3f3f3f;
const int MOD = 998244353;
const int N = 70;
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
namespace Main{
	int q, op, dep;
	ll x, k, mov[N], pw[N];
	void Main(){
		q = read<int>();
		while(q--){
			op = read<int>(), x = read<ll>();
			dep = 63 - __builtin_clzll(x);
			if(op == 1){
				k = read<ll>();
				mov[dep+1] = (mov[dep+1] + (k&((1ll<<dep)-1))) & ((1ll<<dep)-1);
			}
			else if(op == 2){
				k = read<ll>();
				for(ll i = dep, tk = k; i < 64; i++, tk <<= 1)
					mov[i+1] = (mov[i+1] + (tk&((1ll<<i)-1))) & ((1ll<<i)-1);
			}
			else{
				for(ll i = x+mov[dep+1], j = dep; j >= 0; i >>= 1, j--)
					write((i-mov[j+1])&((1ll<<j)-1)|(1ll<<j)), putchar(' ');
				puts("");
			}
		}
		return;
	}
}
int main(){
	Main::Main();
	return 0;
}
