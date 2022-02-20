#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int MOD = 10007;
const int inf = 0x3f3f3f3f;
template<typename T>
inline T read(){
    T n = 0; int f = 1; char ch = getchar();
    while(!isdigit(ch)){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(isdigit(ch)){
        n = n * 10 + ch - '0';
        ch = getchar();
    }
    return f * n;
}
template<typename T>
void write(T n){
    if(n/10) write(n/10);
    putchar(n%10+'0');
}
void input() {}
template<typename Type, typename... Types>
void input(Type &arg, Types&... args){
    arg = read<Type>();
    input(args...);
}
namespace Main{
    ll n, m, fac[MOD], ifac[MOD];
    ll qpow(ll n, ll k){
        ll res = 1;
        while(k > 0){
            if(k & 1) res = res * n % MOD;
            n = n * n % MOD;
            k >>= 1;
        }
        return res;
    }
    ll C(int n, int k) { return fac[n] * ifac[n-k] % MOD * ifac[k] % MOD; }
    ll lucas(int n, int k) { return C(n/MOD, k/MOD) * C(n%MOD, k%MOD); }
    void Main(){
        fac[0] = 1;
        for(ri i = 1; i < MOD; i++) fac[i] = fac[i-1] * i % MOD;
        ifac[MOD-1] = qpow(fac[MOD-1], MOD - 2);
        for(ri i = MOD - 2; i >= 0; i--) ifac[i] = ifac[i+1] * (i + 1) % MOD;
        input(n, m);
        write(C(n * m, n - 1) * qpow(n, MOD - 2) % MOD);
        return;
    }
} // namespace
int main(){
#ifdef Liuxizai
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif // Liuxizai
    Main::Main();
    return 0;
}