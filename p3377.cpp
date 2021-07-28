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
int n, m;
bool deled[100005];
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
namespace Ltree{
    const int SIZE = 100005;
    int v[SIZE], lc[SIZE], rc[SIZE], dist[SIZE];
    int fa[SIZE];
    int find(int x){
        if(fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }
    int merge(int x, int y){
        if(!x || !y) return x | y;
        if(x[v] > y[v] || x[v] == y[v] && x > y) swap(x, y);
        x[rc] = merge(x[rc], y);
        if(x[lc][dist] < x[rc][dist]) swap(x[lc], x[rc]);
        x[dist] = x[rc][dist] + 1;
        return x;
    }
    void del(int x){
        x[lc][fa] = x[rc][fa] = x[fa] = merge(x[lc], x[rc]);
        x[v] = x[lc] = x[rc] = x[dist] = 0;
    }
}
int main(){
    Ltree::dist[0] = -1;
    input(n, m);
    for(ri i = 1; i <= n; i++){
        input(Ltree::v[i]);
        Ltree::fa[i] = i;
    }
    while(m--){
        int op, x, y;
        input(op, x);
        if(op == 1){
            input(y);
            if(deled[x] || deled[y]) continue;
            x = Ltree::find(x), y = Ltree::find(y);
            if(x != y) Ltree::fa[x] = Ltree::fa[y] = Ltree::merge(x, y);
        }
        else{
            if(deled[x]) puts("-1");
            else{
                x = Ltree::find(x);
                deled[x] = true;
                cout << Ltree::v[x] << endl;
                Ltree::del(x);
            }
        }
    }
    return 0;
}