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
    int n, m, ans, cnt;
    bool mp[N][N];
    bool readmp(){
        char ch = getchar();
        while(ch != '.' && ch != '#') ch = getchar();
        return ch == '#';
    }
    void Main(){
        input(n, m);
        for(ri i = 0; i < n; i++){
            for(ri j = 0; j < m; j++){
                mp[i][j] = readmp();
            }
        }
        ans = 0x7fffffff;
        for(ri i = 0; i < n + m - 1; i++){
            for(ri j = max(i-n+1, 0); j < m && i - j > 0; j++){
                if(mp[i-j][j]) cnt++;
                else if(cnt) ans = min(ans, cnt), cnt = 0;
            }
        }
        cnt = 0;
        for(ri i = 1 - m; i < n; i++){
            for(ri j = max(-i, 0); j < m && i + j < n; j++){
                if(mp[i+j][j]) cnt++;
                else if(cnt) ans = min(ans, cnt), cnt = 0;
            }
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