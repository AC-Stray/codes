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
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int N = 4005;
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
    int n, k, a[N][N], s[N][N], f[N][N], p[N][N];
    Int w(int i, int j){
        return s[j][j] - s[j][i-1] - s[i-1][j] + s[i-1][i-1];
    }
    void Main(){
        input(n, k);
        for(ri i = 1; i <= n; i++) for(ri j = 1; j <= n; j++) input(a[i][j]);
        for(ri i = 1; i <= n; i++) for(ri j = 1; j <= n; j++) s[i][j] = a[i][j] + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
        memset(f, 0x3f, sizeof(f));
        for(ri i = 0; i <= k; i++) f[0][i] = 0;
        for(ri j = 1; j <= k; j++){
            p[n+1][j] = n;
            for(ri i = n; i >= 1; i--){
                for(ri k = p[i][j-1]; k <= p[i+1][j]; k++){
                // for(ri k = 0; k < i; k++){
                    if(f[k][j-1] + w(k+1, i) < f[i][j]){
                        f[i][j] = f[k][j-1] + w(k+1, i);
                        p[i][j] = k;
                    }
                }
            }
        }
        write(f[n][k] >> 1);
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