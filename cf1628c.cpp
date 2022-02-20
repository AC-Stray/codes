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
    int t, n, ans, a[N][N];
    bool c[N][N];
    void Main(){
        input(t);
        while(t--){
            ans = 0;
            memset(c, 0, sizeof(c));
            input(n);
            for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) input(a[i][j]);
            for(int i = 2; i <= n; i++) for(int j = 1; j <= n; j++){
                if(!c[i-1][j]){
                    ans ^= a[i][j];
                    c[i-1][j] ^= 1, c[i+1][j] ^= 1;
                    c[i][j-1] ^= 1, c[i][j+1] ^= 1;
                }
            }
            write(ans), puts("");
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