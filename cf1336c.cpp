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
    const int MOD = 998244353;
    const int L = 3005;
    int ls, lt, ans, f[L][L];
    char s[L], t[L];
    void Main(){
        scanf("%s%s", s + 1, t + 1);
        ls = strlen(s + 1), lt = strlen(t + 1);
        for(ri i = 1; i <= lt; i++) if(s[1] == t[i]) f[i][i] = 2;
        for(ri i = lt + 1; i <= ls; i++) f[i][i] = 2;
        for(ri len = 2; len <= ls; len++){
            for(ri i = 1; i + len - 1 <= ls; i++){
                ri j = i + len - 1;
                if(i > lt || s[len] == t[i]) f[i][j] += f[i+1][j];
                if(j > lt || s[len] == t[j]) f[i][j] += f[i][j-1];
                f[i][j] %= MOD;
            }
        }
        for(ri i = lt; i <= ls; i++) ans = (ans + f[1][i]) % MOD;
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