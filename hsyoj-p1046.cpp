#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int N = 100005;
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
    int n, l, v1, v2, t, ans;
    void Main(){
        input(n);
        while(n--){
            input(l, v1, v2, t);
            if(v1 < v2) swap(v1, v2);
            if(v2 == 0) { write((l + t * v1) / l / 2), puts(""); continue; }
            int s1 = t * v1 / l, r1 = t * v1 % l;
            int s2 = t * v2 / l, r2 = t * v2 % l;
            ans = s1;
            if((s1 + s2) & 1) ans += (r1 >= r2);
            else ans += (r1 + r2 >= l);
            int p1 = v1 / __gcd(v1, v2), p2 = v2 / __gcd(v1, v2);
            if((p1 + p2) & 1) ans -= (__gcd(v1, v2) * t / l + 1) / 2;
            write(ans), puts("");
        }
        return;
    }
} // namespace
signed main(){
#ifdef Liuxizai
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif // Liuxizai
    Main::Main();
    return 0;
}