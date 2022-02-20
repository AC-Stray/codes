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
    const int N = 50;
    const int _N = 55;
    struct linearBasis{
        ll a[_N];
        void insert(ll x){
            for(ri i = N; i >= 0; i--){
                if(!(x >> i & 1)) continue;
                if(a[i]) x ^= a[i];
                else{
                    for(ri j = 0; j < i; j++) if(x >> j & 1) x ^= a[j];
                    for(ri j = i + 1; j < N; j++) if(a[j] >> i & 1) a[j] ^= x;
                    a[i] = x;
                    return;
                }
            }
        }
        ll queryMax(){
            ll res = 0;
            for(ri i = 0; i < N; i++) res ^= a[i];
            return res;
        }
    }lb;
    int n;
    void Main(){
        input(n);
        for(ri i = 0; i < n; i++) lb.insert(read<ll>());
        write(lb.queryMax());
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