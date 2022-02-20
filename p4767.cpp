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
const int N = 3005;
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
    int n, m, x[N], sum[N], f[N][N], s[N][N];
    Int w(int l, int r){
        int mid = l + r >> 1;
        return x[mid]*(mid-l+1)-(sum[mid]-sum[l-1]) + (sum[r]-sum[mid])-x[mid]*(r-mid);
    }
    void Main(){
        input(n, m);
        for(ri i = 1; i <= n; i++) input(x[i]);
        sort(x + 1, x + n + 1);
        for(ri i = 1; i <= n; i++) sum[i] = sum[i-1] + x[i];
        memset(f, 0x3f, sizeof(f));
        f[0][0] = 0;
        for(ri j = 1; j <= m; j++){
            s[n+1][j] = n;
            for(ri i = n; i >= 1; i--){
                for(ri k = s[i][j-1]; k <= s[i+1][j]; k++){
                    int tmp;
                    if((tmp = f[k][j-1] + w(k+1, i)) < f[i][j]){
                        f[i][j] = tmp;
                        s[i][j] = k;
                    }
                }
            }
        }
        write(f[n][m]);
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