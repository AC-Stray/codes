#include<bits/stdc++.h>
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
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
void input(Type& arg, Types&... args){
    arg = read<Type>();
    input(args...);
}
namespace Main{
    const int MOD = 1e9 + 7;
    const int N = 1000005;
    ll t, n, m, k, ans, fac[N], ifac[N], itpw[N], inv;
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
        fac[0] = 1;
        for(int i = 1; i < N; i++) fac[i] = fac[i-1] * i % MOD;
        ifac[N-1] = qpow(fac[N-1], MOD - 2);
        for(int i = N - 2; i >= 0; i--) ifac[i] = ifac[i+1] * (i + 1) % MOD;
        inv = qpow(2, MOD - 2), itpw[0] = 1;
        for(int i = 1; i < N; i++) itpw[i] = itpw[i-1] * inv % MOD;
        input(t);
        while(t--){
            input(n, m, k);
            if(n == m) { write(m * k % MOD); puts(""); continue; }
            ans = 0;
            for(int i = 1; i <= m; i++){
                ans = (ans + c(n-i-1, m-i) * itpw[n-i] % MOD * i % MOD * k % MOD) % MOD;
            }
            write(ans), puts("");
        }
        return;
    }
}
int main(){
    Main::Main();
    return 0;
}