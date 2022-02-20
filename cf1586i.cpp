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
const int N = 2005;
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
    int n, g[N][N], color[N];
    bool multi;
    int readmp(){
        char ch = getchar();
        while(ch != '.' && ch != 'S' && ch != 'G') ch = getchar();
        return ch == '.' ? 0 : (ch == 'S' ? 1 : 2);
    }
    void Main(){
        input(n);
        if(n & 1) return puts("NONE"), void();
        for(ri i = 0; i < n; i++){
            if(i & 1)
                for(ri j = i, k = 0; j < n; j++, k++)
                    g[j][k] = (i >> 1) + 1;
            else
                for(ri j = i, k = 0; j >= 0; j--, k++)
                    g[j][k] = (i >> 1) + 1;
        }
        for(ri i = 0; i < n; i++){
            for(ri j = 0; j < n; j++){
                int tmp = readmp();
                if(!tmp) continue;
                if(bool(g[i][j]) ^ (~j&1)) tmp ^= 3;
                if(color[g[i][j]|g[n-i-1][n-j-1]] &&
                   color[g[i][j]|g[n-i-1][n-j-1]] != tmp){
                    puts("NONE");
                    return;
                }
                color[g[i][j]|g[n-i-1][n-j-1]] = tmp;
            }
        }
        multi = false;
        for(ri i = 1; i <= n >> 1; i++) if(!color[i]) multi = true;
        if(multi) return puts("MULTIPLE"), void();
        puts("UNIQUE");
        for(ri i = 0; i < n; i++){
            for(ri j = 0; j < n; j++){
                bool flag = false;
                flag ^= color[g[i][j]|g[n-i-1][n-j-1]] == 1;
                flag ^= bool(g[i][j]) ^ (~j&1);
                putchar(flag ? 'S' : 'G');
            }
            puts("");
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