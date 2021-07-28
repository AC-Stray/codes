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
const int MOD = 1e9+7;
ll n, m, a[105];
vector<int> root;
LL read(){
    ll n = 0; int f = 1; char ch = getchar();
    while('0' > ch || ch > '9'){
        if(ch == '-') f *= -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9'){
        n = (((n << 1) + (n << 3)) % MOD + ch-'0') % MOD;
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
Bool check(int x){
    ll sum = a[n];
    for(ri i = 1; i <= n; i++) sum = (sum * x + a[n-i]) % MOD;
    return sum == 0;
}
int main(){
    // freopen("P2312_2.in", "r", stdin);
    input(n, m);
    for(ri i = 0; i <= n; i++) input(a[i]);
    for(ri i = 1; i <= m; i++)
        if(check(i))
            root.push_back(i);
    cout << root.size() << endl;
    for(ri i = 0; i < root.size(); i++) write(root[i]), puts("");
    return 0;
}