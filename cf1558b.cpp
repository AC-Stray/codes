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
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int N = 4000005;
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
    ll n, sum, MOD, f[N], g[N];
    void Main(){
        input(n, MOD);
        f[1] = 1;
        for(ri i = 1; i <= n; i++){
            sum = (sum + g[i] + f[i-1] + MOD) % MOD;
            f[i] = (f[i] + sum) % MOD;
            for(ri j = 2; i * j <= n; j++){
                g[i*j] = (g[i*j] + f[i]) % MOD;
                if((i + 1) * j <= n) g[(i+1)*j] = (g[(i+1)*j] - f[i] + MOD) % MOD;
            }
        }
        write(f[n]);
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