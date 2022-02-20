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
    const int N = 1000005;
    int t, n, ans, cnt[3];
    char s[N];
    void Main(){
        input(t);
        while(t--){
            input(n);
            scanf("%s", s);
            ans = 0x7fffffff;
            for(ri i = 0; i < n; i++){
                cnt[0] = cnt[1] = cnt[2] = 0;
                for(ri j = i; j < min(i + 7, n); j++){
                    cnt[s[j]-'a']++;
                    if(cnt[0] >= 2 && cnt[0] > cnt[1] && cnt[0] > cnt[2]) ans = min(ans, j - i + 1);
                }
            }
            if(ans == 0x7fffffff) puts("-1");
            else write(ans), puts("");
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