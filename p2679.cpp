#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
const int MOD = 1e9 + 7;
int n, m, k;
int dp[2][205][205][2], use = 1;
char A[1010], B[1010];
LL read(){
	ll n = 0; int f = 1; char ch = getchar();
	while('0' > ch || ch > '9'){
		if(ch == '-') f *= -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9'){
		n = (n << 1) + (n << 3) + ch-'0';
		ch = getchar();
	}
	return f * n;
}
Void write(ll x){
	if(x/10) write(x/10);
	putchar(x%10+'0');
}
Void input() {}
template<typename Type, typename... Types>
Void input(Type& arg, Types&... args){
    arg = read();
    input(args...);
}
int main(){
    input(n, m, k);
    cin >> A+1 >> B+1;
    dp[0][0][0][0] = dp[1][0][0][0] = 1;
    for(ri i = 1; i <= n; i++){
        for(ri j = 1; j <= m; j++){
            for(ri l = 1; l <= k; l++){
                if(A[i] == B[j]){
                    dp[use][j][l][0] = (dp[use^1][j][l][1] + dp[use^1][j][l][0]) % MOD;
                    dp[use][j][l][1] = ((dp[use^1][j-1][l][1] + dp[use^1][j-1][l-1][1]) % MOD + dp[use^1][j-1][l-1][0]) % MOD;
                }
                else{
                    dp[use][j][l][0] = (dp[use^1][j][l][1] + dp[use^1][j][l][0]) % MOD;
                    dp[use][j][l][1] = 0;
                }
            }
        }
        use ^= 1;
    }
    write((dp[n&1][m][k][0] + dp[n&1][m][k][1]) % MOD);
	return 0;
}