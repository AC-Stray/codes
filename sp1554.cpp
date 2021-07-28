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
int t, n, c, e, f, l, ans, cnt[10005][35], dp[10005][35];
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
    input(t);
    while(t--){
        memset(cnt, 0, sizeof(cnt));
        ans = 0;
        input(n, c);
        for(ri i = 0; i < c; i++){
            input(e, f, l);
            int fear = 0, love = 0;
            while(f--) fear |= (1 << ((read()-e+n)%n));
            while(l--) love |= (1 << ((read()-e+n)%n));
            for(ri j = 0; j < 32; j++) if(j & love || ~j & fear) cnt[e][j]++;
        }
        for(ri i = 0; i < 32; i++){
            memset(dp[0], 128, sizeof(dp[0]));
            dp[0][i] = 0;
            for(ri j = 1; j <= n; j++){
                for(ri k = 0; k < 32; k++)
                    dp[j][k] = max(dp[j-1][(k&15)<<1], dp[j-1][(k&15)<<1|1]) + cnt[j][k];
            }
            ans = max(ans, dp[n][i]);
        }
        // cout << ">";
        write(ans);
        puts("");
    }
	return 0;
}