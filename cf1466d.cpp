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
ll t, n, u, v, ans, sum, weight[100005], degree[100005];
vector<int> w;
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
Bool cmp(int a, int b){
    return weight[a] > weight[b];
}
int main(){
    input(t);
    while(t--){
        sum = 0;
        w.clear();
        for(ri i = 1; i <= n; i++) degree[i] = 0;
        input(n);
        for(ri i = 1; i <= n; i++){
            input(weight[i]);
            sum += weight[i];
            w.push_back(i);
        }
        for(ri i = 1; i < n; i++){
            input(u, v);
            degree[u]++;
            degree[v]++;
        }
        sort(w.begin(), w.end(), cmp);
        ans = sum;
        cout << ans << ' ';
        int p = 0;
        for(ri i = 2; i < n; i++){
            while(degree[w[p]] <= 1) p++;
            degree[w[p]]--;
            ans += weight[w[p]];
            cout << ans << ' ';
        }
        puts("");
    }
    return 0;
}