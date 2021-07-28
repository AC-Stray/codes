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
int sh, sm, eh, em, tot, n, idx;
int t[1000005], c[1000005], p[1000005];
int dp[1005];
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
    input(sh, sm, eh, em, n);
    tot = (eh - sh) * 60 + (em - sm);
    for(ri i = 0; i < n; i++){
        int tt, cc, pp;
        input(tt, cc, pp);
        if(pp == 0) pp = 99999;
        int bit = 1;
        while(pp - bit > 0){
            t[idx] = tt * bit, c[idx] = cc * bit, p[idx++] = bit;
            pp -= bit;
            bit <<= 1;
        }
        t[idx] = tt * pp, c[idx] = cc * pp, p[idx++] = pp;
    }
    for(ri i = 0; i < idx; i++){
        for(ri j = tot; j >= t[i]; j--)
            dp[j] = max(dp[j], dp[j-t[i]] + c[i]);
    }
    write(dp[tot]);
	return 0;
}