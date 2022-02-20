#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
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
    const int N = 18;
    const int MOD = 1e9 + 7;
    int n, m, a[N], f[N][1<<N];
    ll ans, fac[1<<N], ifac[1<<N];
    ll qpow(ll n, ll k){
        ll res = 1;
        while(k > 0){
            if(k & 1) res = res * n % MOD;
            n = n * n % MOD;
            k >>= 1;
        }
        return res;
    }
    ll c(int n, int k){
        if(n < k) return 0ll;
        return fac[n] * ifac[n-k] % MOD * ifac[k] % MOD;
    }
    void Main(){
        input(n, m);
        for(int i = 1; i <= m; i++) input(a[i]);
        sort(a + 1, a + m + 1, greater<int>());
        fac[0] = 1;
        for(int i = 1; i <= 1 << n; i++) fac[i] = fac[i-1] * i % MOD;
        ifac[1<<n] = qpow(fac[1<<n], MOD - 2);
        for(int i = (1 << n) - 1; i >= 0; i--) ifac[i] = ifac[i+1] * (i + 1) % MOD;
        f[0][0] = 1;
        for(int i = 1; i <= m; i++){
            for(int s = 0; s < 1 << n; s++){
                f[i][s] = (f[i][s] + f[i-1][s]) % MOD;
                for(int j = 0; j < n; j++){
                    if((s >> j) & 1) continue;
                    f[i][s|(1<<j)] = (f[i][s|(1<<j)] + f[i-1][s] * c((1<<n)-s-a[i], (1<<j)-1) % MOD * fac[1<<j]) % MOD;
                }
            }
        }
        for(int s = 0; s < 1 << n; s++){
            if(__builtin_popcount(s) & 1) ans = (ans - f[m][s] * fac[(1<<n)-s-1] % MOD + MOD) % MOD;
            else ans = (ans + f[m][s] * fac[(1<<n)-s-1] % MOD) % MOD;
        }
        ans = ans * (1 << n) % MOD;
        write(ans);
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