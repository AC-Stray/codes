#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
using namespace std;
using ll = long long;
using ull = unsigned long long;
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
void input(Type& arg, Types&... args){
    arg = read<Type>();
    input(args...);
}
namespace Main{
    const int N = 200005;
    ll n, q, a[N], c[N];
    void Main(){
        input(n);
        for(int i = 1; i <= n; i++){
            input(a[i]);
            c[i] = 1;
            while(~a[i] & 1) a[i] >>= 1, c[i] <<= 1;
        }
        for(int i = 2; i <= n; i++) c[i] += c[i-1];
        input(q);
        while(q--){
            ll p = read<ll>();
            write(a[lower_bound(c + 1, c + n + 1, p) - c]);
            puts("");
        }
        return;
    }
}
int main(){
    #ifdef Liuxizai
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    #endif
    Main::Main();
    return 0;
}