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
    const int N = 105;
    const int L = 30;
    ll k, sum, a[N];
    struct linearBasis{
        int t[L];
        bool insert(int x){
            int save = x;
            for(ri i = L - 1; i >= 0; i--){
                if(!(x >> i & 1)) continue;
                if(!t[i]) return t[i] = x, true;
                else x ^= t[i];
            }
            return false;
        }
    }lb;
    void Main(){
        input(k);
        for(ri i = 0; i < k; i++) input(a[i]);
        sort(a, a + k, greater<int>());
        for(ri i = 0; i < k; i++) if(!lb.insert(a[i])) sum += a[i];
        write(sum);
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