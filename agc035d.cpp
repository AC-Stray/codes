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
    const ll inf = 1e18;
    const int N = 20;
    int n, a[N];
    ll solve(int l, int r, ll x, ll y){
        if(l > r) return 0;
        ll res = inf;
        for(int i = l; i <= r; i++){
            res = min(res, solve(l, i - 1, x, x + y) + solve(i + 1, r, x + y, y) + (x + y) * a[i]);
        }
        return res;
    }
    void Main(){
        input(n);
        for(int i = 0; i < n; i++) input(a[i]);
        write(solve(1, n - 2, 1, 1) + a[0] + a[n-1]);
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