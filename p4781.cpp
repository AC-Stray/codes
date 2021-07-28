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
const int MOD = 998244353;
ll n, k, ans, x[2005], y[2005];
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
LL qpow(ll n, ll k){
    ll res = 1;
    while(k > 0){
        if(k & 1) res = res * n % MOD;
        n = n * n % MOD;
        k >>= 1;
    }
    return res;
}
int main(){
    input(n, k);
    for(ri i = 0; i < n; i++) input(x[i], y[i]);
    for(ri i = 0; i < n; i++){
        ll res = y[i];
        for(ri j = 0; j < n; j++){
            if(i == j) continue;
            res = res * (k + MOD - x[j]) % MOD * qpow((x[i]-x[j]+MOD)%MOD, MOD-2) % MOD;
        }
        ans = (ans + res) % MOD;
    }
    write(ans);
    return 0;
}