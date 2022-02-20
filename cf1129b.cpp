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
    const int N = 2005;
    int k, x, y, n, a[N];
    int alice(){
        int res = 0, cur = 0, k = -1;
        for(ri i = 0; i < n; i++){
            cur = cur + a[i];
            if(cur < 0){
                cur = 0;
                k = i;
            }
            res = max(res, (i - k) * cur);
        }
        return res;
    }
    void Main(){
        input(k);
        n = 2;
        a[0] = -1, a[1] = 1;
        k++;
        while(k) a[n] = min(1000000, k + 1), k -= a[n++] - 1;
        cout << n << endl;
        for(ri i = 0; i < n; i++) cout << a[i] << ' ';
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