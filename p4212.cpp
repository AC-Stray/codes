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
int n, u, ans, v, p[55];
bool fri[55][55];
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
    srand(rand());
    input(n);
    while(cin >> u >> v){
        fri[u][v] = fri[v][u] = true;
    }
    for(ri i = 1; i <= n; i++) p[i] = i;
    while((double)clock() / CLOCKS_PER_SEC < 0.8){
        for(re double T = 200000; T > 1e-18; T *= 0.998){
            int x = rand()%n+1, y = rand()%n+1;
            while(x == y) x = rand()%n+1, y = rand()%n+1;
            swap(p[x], p[y]);
            int cnt = 0, res[55];
            for(ri i = 1; i <= n; i++){
                res[++cnt] = p[i];
                for(ri j = 1; j < cnt; j++) if(!fri[p[i]][res[j]]){
                    cnt--;
                    break;
                }
            }
            int Derta = cnt - ans;
            if(Derta > 0) ans = cnt;
            else if(exp(-Derta / T) <= rand() / RAND_MAX) swap(p[x], p[y]);
        }
    }
    write(ans);
    return 0;
}