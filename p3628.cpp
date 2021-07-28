#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
int n, a, b, c, s[1000005], dp[1000005];
int head, tail, q[1000005];
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
Int K(int i){ return 2 * a * s[i]; }
Int X(int j){ return s[j]; }
Int B(int i){ return dp[i] - a*s[i]*s[i] - b*s[i] - c; }
Int Y(int j){ return dp[j] + a*s[j]*s[j] - b*s[j]; }
inline double slope(int i, int j){ return 1.0 * (Y(i)-Y(j)) / (X(i)-X(j)); }
signed main(){
    input(n);
    input(a, b, c);
    for(ri i = 1; i <= n; i++) s[i] = s[i-1] + read();
    for(ri i = 1; i <= n; i++){
        while(head < tail && slope(q[head], q[head+1]) > K(i)) head++;
        dp[i] = -K(i)*X(q[head]) + Y(q[head]) + a*s[i]*s[i] + b*s[i] + c;
        while(head < tail && slope(q[tail-1], q[tail]) <= slope(q[tail], i)) tail--;
        q[++tail] = i;
    }
    write(dp[n]);
	return 0;
}