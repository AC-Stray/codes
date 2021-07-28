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
int a[100005][105], n, d, k;
int s1[105], s2[105][105];
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
Bool check(int p, int q){
    int sum = 0;
    for(ri i = 0; i < d; i++) sum += a[p][i] * a[q][i];
    return sum % k == 0;
}
Int solve(int p){
    int sum = 0;
    if(k == 2)
        for(ri i = 0; i < d; i++)
            sum += s1[i] * a[p][i], s1[i] += a[p][i];
    else
        for(ri i = 0; i < d; i++) for(ri j = 0; j < d; j++)
            sum += s2[i][j] * a[p][i] * a[p][j], s2[i][j] += a[p][i] * a[p][j];
    return sum % k;
}
int main(){
    input(n, d, k);
    for(ri i = 0; i < n; i++) for(ri j = 0; j < d; j++) a[i][j] = read() % k;
    for(ri i = 0; i < n; i++){
        if(solve(i) != i % k){
            for(ri j = 0; j < i; j++) if(check(i, j)){
                cout << j+1 << ' ' << i+1;
                return 0;
            }
        }
    }
    puts("-1 -1");
    return 0;
}