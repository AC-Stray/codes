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
int n, m, t, k, cnt, c[55], id[55][10];
ll f[55];
struct matrix{
    ll v[255][255];
    matrix(){
        memset(v, 0xc0, sizeof(matrix));
    }
    Void print(){
        for(ri i = 1; i <= cnt; i++){
            for(ri j = 1; j <= cnt; j++){
                cout << setw(3) << (v[i][j]<0?-1:v[i][j]) << ' ';
            }
            cout << endl;
        }
    }
    ll* operator [] (const int &index){
        return v[index];
    }
    const ll* operator [] (const int &index) const {
        return v[index];
    }
    matrix operator * (const matrix &b){
        matrix res;
        for(ri i = 1; i <= cnt; i++){
            for(ri k = 1; k <= cnt; k++){
                if(v[i][k] < 0) continue;
                for(ri j = 1; j  <= cnt; j++){
                    res[i][j] = max(res[i][j], v[i][k] + b[k][j]);
                }
            }
        }
        return res;
    }
}G[35];
struct fest{
    int t, x, y;
    Bool operator < (const fest &b) const {
        return t < b.t;
    }
}fests[205];
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
    input(n, m, t, k);
    for(ri i = 1; i <= n; i++) input(c[i]);
    for(ri i = 1; i <= n; i++) id[i][0] = i;
    cnt = n;
    for(ri i = 0; i < m; i++){
        int u, v, w;
        input(u, v, w);
        for(ri j = 1; j < w; j++) if(!id[u][j]) id[u][j] = ++cnt;
        for(ri j = 1; j < w; j++) G[0][id[u][j-1]][id[u][j]] = 0;
        G[0][id[u][w-1]][v] = c[v];
    }
    for(ri i = 1; i < 30; i++) G[i] = G[i-1] * G[i-1];
    // for(ri i = 0; i <= 3; i++){
    //     for(ri j = 1; j <= cnt; j++){
    //         for(ri k = 1; k <= cnt; k++) cout << G[i][j][k] << ' ';
    //         cout << endl;
    //     }
    //     cout << endl;
    // }
    for(ri i = 1; i <= k; i++) input(fests[i].t, fests[i].x, fests[i].y);
    fests[0] = {0, 0, 0}, fests[k+1] = {t, 0, 0};
    sort(fests+1, fests+k+1);
    for(ri i = 2; i <= cnt; i++) f[i] = -4e18;
    f[1] = c[1];
    for(ri i = 1; i <= k+1; i++){
        int delta = fests[i].t - fests[i-1].t;
        for(ri j = 30; j >= 0; j--) if(delta & (1<<j)){
            ll F[55];
            for(ri k = 1; k <= cnt; k++) F[k] = -4e18;
            for(ri k = 1; k <= cnt; k++){
                if(f[k] < 0) continue;
                for(ri l = 1; l <= cnt; l++){
                    F[l] = max(F[l], f[k]+G[j][k][l]);
                }
            }
            for(ri k = 1; k <= cnt; k++) f[k] = F[k];
        }
        f[fests[i].x] += fests[i].y;
    }
    if(f[1] < 0) puts("-1");
    else write(f[1]);
    return 0;
}