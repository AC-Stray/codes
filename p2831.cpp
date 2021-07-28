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
const double eps = 1e-8;
int t, n, m, line[20][20], start[1<<19], dp[1<<19];
double x[20], y[20];
Void calc(double &a, double &b, int i, int j){
	a = -(y[i]*x[j] - y[j]*x[i]) / (x[j]*x[j]*x[i] - x[i]*x[i]*x[j]);
	b = (y[i]*x[j]*x[j] - y[j]*x[i]*x[i]) / (x[i]*x[j]*x[j] - x[j]*x[i]*x[i]);
}
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
    for(ri i = 0; i < (1<<18); i++){
        int j = 0;
        while(i & (1<<j)) j++;
        start[i] = j;
    }
    input(t);
    while(t--){
        memset(dp, 0x3f, sizeof(dp)); dp[0] = 0;
        memset(line, 0, sizeof(line));
        input(n, m);
        for(ri i = 0; i < n; i++) scanf("%lf %lf", &x[i], &y[i]);
        for(ri i = 0; i < n; i++){
            for(ri j = 0; j < n; j++){
                if(fabs(x[i]-x[j]) < eps) continue;
                double a, b;
                calc(a, b, i, j);
                if(a > -eps) continue;
                for(ri k = 0; k < n; k++)
                    if(fabs(a*x[k]*x[k] + b*x[k] - y[k]) < eps) line[i][j] |= 1 << k;
            }
        }
        for(ri i = 0; i < (1<<n); i++){
            dp[i|(1<<start[i])] = min(dp[i|(1<<start[i])], dp[i]+1);
            for(ri j = 0; j < n; j++) dp[i|line[start[i]][j]] = min(dp[i|line[start[i]][j]], dp[i]+1);
        }
        write(dp[(1<<n)-1]); puts("");
    }
    return 0;
}