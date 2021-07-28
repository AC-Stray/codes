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
ll t, k, n, maxCnt, maxColor, ans, ANS, ctn, brk, c[100005], cnt[105];
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
        input(n, k);
        for(ri i = 0; i < n; i++) input(c[i]), cnt[c[i]]++;
        ANS = 0x7fffffff;
        for(ri color = 1; color <= 100; color++){
            if(cnt[color] == 0) continue;
            int p = 0;
            ans = 0;
            while(p < n){
                if(c[p] == color) p++;
                else{
                    p += k;
                    ans++;
                }
            }
            ANS = min(ANS, ans);
        }
        write(ANS), puts("");
    }
	return 0;
}