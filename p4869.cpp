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
    const int MOD = 10086;
    const int L = 30;
    int cnt = 0;
    struct linearBasis{
        int t[L];
        void insert(int x){
            for(ri i = L - 1; i >= 0; i--){
                if(!(x >> i & 1)) continue;
                if(!t[i]) return t[i] = x, void();
                else x ^= t[i];
            }
            cnt++;
        }
    }lb;
    int n, q;
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
        input(n);
        for(ri i = 0; i < n; i++) lb.insert(read<ll>());
        input(q);
        ll rank = 0, trk = 1;
        for(ri i = 0; i < L; i++){
            if(!lb.t[i]) continue;
            if(q >> i & 1) rank = (rank + trk) % MOD;
            trk = (trk << 1) % MOD;
        }
        write((rank * qpow(2, cnt) + 1) % MOD);
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