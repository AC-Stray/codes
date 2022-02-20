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
const int MOD = 999911659;
const int inf = 0x3f3f3f3f;
const int N = 505;
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
    ll n, val, ans, inv[10], f[N][N][10], cnt[N];
    int p, beg, len, pos[N];
    ll C(int n, int k){
        ll res = inv[k];
        for(ri i = n; i >= n - k + 1; i--) res = res * i % MOD;
        return res;
    }
    void Main(){
        input(n, p);
        for(ri i = 1; i <= n; i++){
            val = (val * 10 + 1) % p;
            if(pos[val]){
                beg = pos[val];
                len = i - beg;
                break;
            }
            pos[val] = i;
            cnt[val]++;
        }
        for(ri i = 0; len && i < p; i++){
            if(pos[i] && pos[i] >= beg){
                cnt[i] = (cnt[i] + (n - pos[i]) / len) % MOD;
                if((pos[i] - beg + 1) % len == (n - beg + 1) % len) val = i;
            }
        }
        // for(ri i = 0; i < p; i++) cout << cnt[i] << ' '; cout << endl;
        inv[0] = inv[1] = 1;
        for(ri i = 2; i < 10; i++) inv[i] = (MOD-MOD/i) * inv[MOD%i] % MOD;
        for(ri i = 2; i < 10; i++) inv[i] = inv[i] * inv[i-1] % MOD;
        f[0][val][0] = 1;
        for(ri i = 0; i < p; i++){
            for(ri j = 0; j < p; j++){
                for(ri k = 0; k < 9; k++){
                    for(ri c = 0; c < 9 - k; c++){
                        f[i+1][(j+c*i)%p][k+c] += f[i][j][k] * C(cnt[i]+c-1, c) % MOD;
                        f[i+1][(j+c*i)%p][k+c] %= MOD;
                    }
                }
            }
        }
        for(ri i = 0; i < 9; i++) ans = (ans + f[p][0][i]) % MOD;
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