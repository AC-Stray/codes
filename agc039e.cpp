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
    int n;
    ll f[N][N][N], ans;
    char s[N][N];
    ll dfs(int l, int p, int r){
        if(l == r) return 1ll;
        if(f[l][p][r] >= 0) return f[l][p][r];
        f[l][p][r] = 0;
        for(int i = l; i <= r; i++) for(int j = i + 1; j <= r; j++){
            if(s[i][j] == '0') continue;
            for(int k = i; k < p; k++) for(int m = p; m < j; m++){
                f[l][p][r] += dfs(l, i, k) * dfs(k + 1, p, m) * dfs(m + 1, j, r);
            }
        }
        return f[l][p][r];
    }
    void Main(){
        input(n); n <<= 1;
        for(int i = 1; i <= n; i++) scanf("%s", s[i] + 1);
        memset(f, -1, sizeof(f));
        for(int i = 2; i <= n; i++) if(s[1][i] == '1') ans += dfs(2, i, n);
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