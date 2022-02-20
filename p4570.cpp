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
    const int N = 1005;
    const int L = 60;
    struct linearBasis{
        ll t[L];
        bool insert(ll x){
            for(ri i = L - 1; i >= 0; i--){
                if(!(x >> i & 1)) continue;
                if(!t[i]) return t[i] = x, true;
                else x ^= t[i];
            }
            return false;
        }
    }lb;
    int n, ans;
    struct mineral{
        ll num; int maj;
        bool operator < (const mineral &b) const { return maj > b.maj; }
    }a[N];
    void Main(){
        input(n);
        for(ri i = 0; i < n; i++) input(a[i].num, a[i].maj);
        sort(a, a + n);
        for(ri i = 0; i < n; i++) if(lb.insert(a[i].num)) ans += a[i].maj;
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