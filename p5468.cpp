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
struct train{
    int x, y, p, q;
    Bool operator < (const train &b){
        return p < b.p;
    }
}t[200005];
int n, m, A, B, C, ans;
int dp[1005][100005];
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
Int cal(int x){
    return A*x*x + B*x + C;
}
int main(){
    input(n, m, A, B, C);
    for(ri i = 0; i < m; i++) input(t[i].x, t[i].y, t[i].p, t[i].q);
    sort(t, t+m);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][1] = 0;
    for(ri i = 0; i < m; i++)
        for(ri j = 0; j <= t[i].p; j++)
            dp[t[i].q][t[i].y] = min(dp[t[i].q][t[i].y], dp[j][t[i].x] + cal(t[i].p-j));
    ans = 0x3f3f3f3f;
    for(ri i = 0; i <= t[m-1].q; i++) ans = min(ans, dp[i][n]+i);
    write(ans);
    return 0;
}