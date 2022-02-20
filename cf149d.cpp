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
const int N = 710;
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
	int cnt, match[N];
	ll ans, f[N][N][3][3];
	bool seq[N];
	stack<int> brt;
	void input(){
		char ch = getchar();
		while(ch != '(' && ch != ')') ch = getchar();
		while(ch == '(' || ch == ')'){
			cnt++;
			if(ch == '(') seq[cnt] = true;
			ch = getchar();
		}
	}
	void dfs(int l, int r){
		if(r - l == 1) f[l][r][1][0] = f[l][r][2][0] = f[l][r][0][1] = f[l][r][0][2] = 1;
		else if(r == match[l]){
			dfs(l + 1, r - 1);
			for(ri i = 0; i <= 2; i++){
				for(ri j = 0; j <= 2; j++){
					if(i != 1) f[l][r][1][0] = (f[l][r][1][0] + f[l+1][r-1][i][j]) % MOD;
					if(i != 2) f[l][r][2][0] = (f[l][r][2][0] + f[l+1][r-1][i][j]) % MOD;
					if(j != 1) f[l][r][0][1] = (f[l][r][0][1] + f[l+1][r-1][i][j]) % MOD;
					if(j != 2) f[l][r][0][2] = (f[l][r][0][2] + f[l+1][r-1][i][j]) % MOD;
				}
			}
		}
		else{
			dfs(l, match[l]), dfs(match[l] + 1, r);
			for(ri i = 0; i <= 2; i++){
				for(ri j = 0; j <= 2; j++){
					for(ri k = 0; k <= 2; k++){
						for(ri p = 0; p <= 2; p++){
							if(j == k && j != 0) continue;
							f[l][r][i][p] = (f[l][r][i][p] + f[l][match[l]][i][j] * f[match[l]+1][r][k][p] % MOD) % MOD;
						}
					}
				}
			}
		}
	}
	void Main(){
		input();
		for(ri i = 1; i <= cnt; i++){
			if(seq[i]) brt.push(i);
			else match[brt.top()] = i, brt.pop();
		}
		dfs(1, cnt);
		cerr << f[1][6][0][1] << ' ' << f[1][6][0][2] << endl;
		for(ri i = 0; i <= 2; i++){
			for(ri j = 0; j <= 2; j++){
				ans = (ans + f[1][cnt][i][j]) % MOD;
			}
		}
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

