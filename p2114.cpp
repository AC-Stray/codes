#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
int n, m, t, ans, a = 0, b = 0x7fffffff;
string op;
LL read(){
    ll n = 0; int f = 1; char ch = getchar();
    while('0' > ch || ch > '9'){
        if(ch == '-') f *= -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9'){
        n = (n << 1) + (n << 3) + ch-'0';
        ch = getchar();
    }
    return f * n;
}
Void write(ll x){
    if(x/10) write(x/10);
    putchar(x%10+'0');
}
Void input() {}
template<typename Type, typename... Types>
Void input(Type& arg, Types&... args){
    arg = read();
    input(args...);
}
int main(){
    cin >> n >> m;
    for(ri i = 0; i < n; i++){
        cin >> op >> t;
             if(op == "AND") a &= t, b &= t;
        else if(op == "OR")  a |= t, b |= t;
        else if(op == "XOR") a ^= t, b ^= t;
    }
    for(ri i = 30; i >= 0; i--){
        if((a >> i) & 1) ans += (1 << i);
        else if(((b >> i) & 1) && (1 << i) <= m) ans += (1 << i), m -= (1 << i);
    }
    write(ans);
    return 0;
}