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
const int N = 1005;
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
    int n, tot;
    struct line{
        int u, v;
        line() {}
        line(int u, int v): u(u), v(v) {}
    };
    vector<line> ans1[N], ans2[N];
    set<int> ext;
    void Main(){
        input(n);
        for(ri i = 0, u, v; i < n - 3; i++){
            input(u, v);
            if(u == 1 || v == 1) continue;
            if(u < v) swap(u, v);
            ans1[u - v].emplace_back(u, v);
            tot++;
        }
        for(ri i = 0, u, v; i < n - 3; i++){
            input(u, v);
            if(u == 1 || v == 1) continue;
            if(u < v) swap(u, v);
            ans2[u - v].emplace_back(u, v);
            tot++;
        }
        write(tot); puts("");
        for(ri i = N - 1; i; i--) for(line x: ans1[i]) printf("%d %d\n", x.u, x.v);
        for(ri i = 3; i <= n - 1; i++) ext.emplace(i);
        for(ri i = 1; i < N; i++){
            for(line x: ans2[i]){
                set<int>::iterator iter = ext.upper_bound(x.v);
                printf("%d %d\n", 1, *iter);
                ext.erase(iter);
            }
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