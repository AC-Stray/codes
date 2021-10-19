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
const int MOD = 1e9 + 7;
const int N = 200005;
const int M = 505;
#ifdef ONLINE_JUDGE
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
char buf[100000], *p1(buf), *p2(buf);
#endif
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
	int n, m, siz, blocks, op, x, y, z, l, r, a[N], bl[M], br[M], pos[N];
	ll ans, sum[M], add[M][M];
	void Main(){
		n = read<int>(), m = read<int>();
		for(ri i = 1; i <= n; i++) a[i] = read<int>();
		siz = sqrt(n);
		blocks = (n - 1) / siz + 1;
		for(ri i = 0; i < blocks; i++){
			bl[i] = i * siz + 1;
			br[i] = (i == blocks - 1 ? n : (i+1)*siz);
			for(ri j = bl[i]; j <= br[i]; j++){
				pos[j] = i;
				sum[i] += a[j];
			}
			sum[i] %= MOD;
		}
		while(m--){
			op = read<int>();
			if(op == 1){
				x = read<int>(), y = read<int>(), z = read<int>();
				if(x > siz){	
					for(ri i = y; i <= n; i += x){
						sum[pos[i]] = (sum[pos[i]] + z) % MOD;
						a[i] = (a[i] + z) % MOD;
					}
				}
				else{
					for(ri i = y; i <= x; i++)
						add[x][i] = (add[x][i] + z) % MOD;
				}
			}
			else{
				l = read<int>(), r = read<int>();
				ans = 0;
				if(pos[l] == pos[r]) for(ri i = l; i <= r; i++) ans += a[i];
				else{
					for(ri i = pos[l] + 1; i <= pos[r] - 1; i++) ans += sum[i];
					for(ri i = l; i <= br[pos[l]]; i++) ans += a[i];
					for(ri i = bl[pos[r]]; i <= r; i++) ans += a[i];
				}
				for(ri i = 1; i <= siz; i++){
					ans += r / i * add[i][i] + add[i][r%i];
					ans += (MOD << 1) - (l - 1) / i * add[i][i] - add[i][(l-1)%i];
				}
				write(ans % MOD); puts("");
			}
		}
		return;
	}
}
int main(){
	Main::Main();
	return 0;
}
