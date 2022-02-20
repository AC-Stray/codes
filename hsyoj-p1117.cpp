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
    const int N = 100005;
    const int MOD = 998244353;
    int n, m, deg[N];
    ll inv[N], ans;
    void Main(){
        input(n, m);
        for(ri i = 0, u, v; i < m; i++){
            input(u, v);
            deg[u]++, deg[v]++;
        }
        inv[1] = 1;
        for(ri i = 2; i <= n; i++) inv[i] = (MOD-MOD/i) * inv[MOD%i] % MOD;
        for(ri i = 1; i <= n; i++) ans = (ans + deg[i] * inv[deg[i] + 1] % MOD) % MOD;
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