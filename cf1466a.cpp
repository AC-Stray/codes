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
int t, n, x[55];
vector<int> len;
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
    input(t);
    while(t--){
        len.clear();
        input(n);
        for(ri i = 0; i < n; i++) input(x[i]);
        for(ri i = 0; i < n; i++) for(ri j = i+1; j < n; j++) len.push_back(x[j]-x[i]);
        // cout << ">";
        sort(len.begin(), len.end());
        write(unique(len.begin(), len.end())-len.begin());
        puts("");
    }
    return 0;
}