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
int n, m, k, ans;
int d[1005], arrive[1005], latest[1005], off[1005];
int t[10005], a[10005], b[10005];
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
    for(ri i = 0; i < n-1; i++) input(d[i]);
    for(ri i = 0; i < m; i++){
        input(t[i], a[i], b[i]);
        latest[a[i]] = max(latest[a[i]], t[i]);
        off[b[i]]++;
    }
    arrive[1] = 0;
    int timeCnt = latest[1];
    for(ri i = 2; i <= n; i++){
        arrive[i] = timeCnt + d[i-2];
        timeCnt = max(arrive[i], latest[i]);
    }
    while(k--){
        int maxv = 0, maxp;
        for(ri i = 0; i < n-1; i++){
            if(d[i] == 0) continue;
            int tmp = 0;
            for(ri j = i+2; j <= n; j++){
                tmp += off[j];
                if(arrive[j] - 1 < latest[j]) break;
            }
            if(tmp > maxv){
                maxv = tmp;
                maxp = i;
            }
        }
        d[maxp]--;
        for(ri i = maxp; i < n-1; i++){
            arrive[i+2]--;
            if(arrive[i+2] < latest[i+2]) break;
        }
    }
    for(ri i = 0; i < m; i++) ans += arrive[b[i]] - t[i];
    cout << ans;
    return 0;
}