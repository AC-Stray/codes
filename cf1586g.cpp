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
const int MOD = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const int N = 400005;
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
    int n, t, l, a[N], b[N], rev[N], lst[N];
    ll ans, f[N];
    bool s[N];
    struct bintree{
        ll v[N];
        void clear() { memset(v, 0, sizeof(v)); }
        Int lowbit(int x) { return x & -x; }
        void add(int x, int k){
            while(x){
                v[x] = (v[x] + k) % MOD;
                x -= lowbit(x);
            }
        }
        int query(int x){
            int res = 0;
            while(x < N){
                res = (res + v[x]) % MOD;
                x += lowbit(x);
            }
            return res;
        }
    }tree;
    void Main(){
        input(n);
        for(ri i = 1; i <= n; i++){
            int tmp = read<int>();
            input(b[i]);
            a[b[i]] = tmp;
        }
        input(t);
        for(ri i = 0; i < t; i++) s[b[read<int>()]] = true;
        for(ri i = n << 1; i >= 1; i--){
            if(!s[i]) continue;
            if(a[i] < l) s[i] = false;
            else{
                lst[i] = l;
                l = a[i];
            }
        }
        for(ri i = 1; i <= n << 1; i++){
            if(!a[i]) continue;
            f[i] = (tree.query(a[i]) + 1) % MOD;
            tree.add(a[i], f[i]);
        }
        tree.clear();
        for(ri i = 1; i <= n << 1; i++){
            if(!a[i]) continue;
            if(s[i]) ans = (ans + tree.query(lst[i] + 1) + 1) % MOD;
            tree.add(a[i], f[i]);
        }
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