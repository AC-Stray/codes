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
    const int MOD = 998244353;
    const int N = 1000005;
    int T, n, k, cnt;
    ll f[N], pw[N], pri[N], mu[N], ans;
    bool vis[N];
    void init(){
        mu[1] = 1;
        for(ri i = 2; i < N; i++){
            if(!vis[i]){
                mu[i] = MOD - 1;
                pri[cnt++] = i;
            }
            for(ri j = 0; j < cnt; j++){
                if(i * pri[j] >= N) break;
                vis[i * pri[j]] = true;
                if(i % pri[j] == 0){
                    mu[i * pri[j]] = 0;
                    break;
                }
                mu[i * pri[j]] = (MOD - mu[i]) % MOD;
            }
        }
    }
    ll qpow(ll n, ll k){
        ll res = 1;
        while(k > 0){
            if(k & 1) res = res * n % MOD;
            n = n * n % MOD;
            k >>= 1;
        }
        return res;
    }
    void Main(){
        init();
        input(T);
        while(T--){
            input(n, k);
            for(ri i = 1; i <= k; i++) pw[i] = qpow(k / i, n);
            memset(f, 0, sizeof(f));
            for(ri i = 1; i <= k; i++){
                for(ri j = i; j <= k; j += i){
                    f[i] = (f[i] + mu[j/i] * pw[j] % MOD) % MOD;
                }
            }
            ans = 0;
            for(ri i = 1; i <= k; i++) ans = (ans + f[i] * i % MOD) % MOD;
            write(ans * qpow(qpow(k, n), MOD - 2) % MOD);
            puts("");
        }
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