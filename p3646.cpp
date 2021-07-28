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
int n, a, b, sum, y[2005], dp2[2005];
bool dp[2005][2005];
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
namespace Solve1{
    Int solve(){
        int ans = 0, tmp = 0;
        for(ri i = log2(sum)+1; i >= 0; i--){
            tmp = ans | ((1ll<<i) - 1ll);
            memset(dp, 0, sizeof(dp));
            dp[0][0] = true;
            for(ri j = 0; j < n; j++){
                for(ri k = 1; k <= min(j+1, b); k++){
                    int tsum = 0;
                    for(ri l = j; l >= k-1; l--){
                        tsum += y[l];
                        if(dp[l][k-1] && ((tsum | tmp) == tmp)){
                            dp[j+1][k] = true;
                            break;
                        }
                    }
                }
            }
            bool flag = false;
            for(ri j = a; j <= b; j++){
                if(dp[n][j]){
                    flag = true;
                    break;
                }
            }
            if(!flag) ans |= 1ll << i;
        }
        return ans;
    }
}
namespace Solve2{
    Int solve(){
        int ans = 0, tmp = 0;
        for(ri i = log2(sum)+1; i >= 0; i--){
            tmp = ans | ((1ll<<i) - 1ll);
            memset(dp2, 0x3f, sizeof(dp2));
            dp2[0] = 0;
            for(ri j = 0; j < n; j++){
                int tsum = 0;
                for(ri k = j; k >= 0; k--){
                    tsum += y[k];
                    if((tsum | tmp) == tmp) dp2[j+1] = min(dp2[j+1], dp2[k]+1);
                }
            }
            if(dp2[n] > b) ans |= 1ll << i;
        }
        return ans;
    }
}
signed main(){
    input(n, a, b);
    for(ri i = 0; i < n; i++) input(y[i]), sum += y[i];
    if(a == 1) cout << Solve2::solve();
    else cout << Solve1::solve();
    return 0;
}