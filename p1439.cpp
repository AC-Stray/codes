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
int n, b[100005];
int dp[100005], len;
struct node{
    int p, v;
    Bool operator < (const node &b) const { return v < b.v; }
}a[100005];
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
    input(n);
    for(ri i = 0; i < n; i++) input(a[i].v), a[i].p = i;
    sort(a, a+n);
    for(ri i = 0; i < n; i++) b[i] = a[read()-1].p+1;
    // for(ri i = 0; i < n; i++) cout << b[i] << ' ';
    memset(dp, 0x3f, sizeof(dp));
    dp[1] = b[0];
    len = 1;
    for(ri i = 1; i < n; i++){
        if(b[i] > dp[len]) dp[++len] = b[i];
        else{
            int* p = lower_bound(dp+1, dp+len+1, b[i]);
            *p = min(*p, b[i]); 
        }
    }
    write(len);
	return 0;
}