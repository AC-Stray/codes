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
    const int cnt = 8, pri[] = {2, 3, 5, 7, 11, 13, 17, 19};
    ll n, MOD, ans, f[N][N], g1[N][N], g2[N][N];
    struct number{
        int bp, s;
        number() {}
        number(int x){
            bp = x, s = 0;
            for(ri i = 0; i < cnt; i++){
                while(bp % pri[i] == 0){
                    s |= 1 << i;
                    bp /= pri[i];
                }
            }
        }
        bool operator < (const number &b) const { return bp < b.bp; }
    }num[N];
    void Main(){
        input(n, MOD);
        for(ri i = 0; i < n - 1; i++) num[i] = number(i + 2);
        sort(num, num + n - 1);
        f[0][0] = 1;
        for(ri i = 0; i < n - 1; i++){
            if(i == 0 || num[i].bp != num[i-1].bp || num[i].bp == 1){
                memcpy(g1, f, sizeof(f));
                memcpy(g2, f, sizeof(f));
            }
            for(ri j = (1 << cnt) - 1; j >= 0; j--){
                for(ri k = (1 << cnt) - 1; k >= 0; k--){
                    if(j & k) continue;
                    if(!(num[i].s&j)) g2[j][k|num[i].s] = (g2[j][k|num[i].s] + g2[j][k]) % MOD;
                    if(!(num[i].s&k)) g1[j|num[i].s][k] = (g1[j|num[i].s][k] + g1[j][k]) % MOD;
                }
            }
            if(i == n - 2 || num[i].bp != num[i+1].bp || num[i].bp == 1){
                for(ri j = 0; j < 1 << cnt; j++){
                    for(ri k = 0; k < 1 << cnt; k++){
                        if(j & k) continue;
                        f[j][k] = (g1[j][k] + g2[j][k] - f[j][k] + MOD) % MOD;
                    }
                }
            }
        }
        for(ri i = 0; i < 1 << cnt; i++){
            for(ri j = 0; j < 1 << cnt; j++){
                if(i & j) continue;
                ans = (ans + f[i][j]) % MOD;
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