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
    const int N = 100005;
    int T, na, nb, nc;
    ll ans;
    vector<int> a, b, c;
    LL s(int x) { return 1ll * x * x; }
    void solve(vector<int> a, vector<int> b, vector<int> c){
        for(ri i = 0, j = 0, k = 0; i < b.size(); i++){
            while(j < a.size() - 1 && a[j + 1] <= b[i]) j++;
            while(k < c.size() - 1 && c[k] < b[i]) k++;
            if(a[j] > b[i] || c[k] < b[i]) continue;
            ans = min(ans, s(b[i]-a[j]) + s(c[k]-b[i]) + s(c[k]-a[j]));
        }
    }
    void Main(){
        input(T);
        while(T--){
            input(na, nb, nc);
            a.resize(na), b.resize(nb), c.resize(nc);
            for(ri i = 0; i < na; i++) input(a[i]);
            for(ri i = 0; i < nb; i++) input(b[i]);
            for(ri i = 0; i < nc; i++) input(c[i]);
            sort(a.begin(), a.end());
            sort(b.begin(), b.end());
            sort(c.begin(), c.end());
            ans = 9e18;
            solve(a, b, c), solve(a, c, b);
            solve(b, a, c), solve(b, c, a);
            solve(c, a, b), solve(c, b, a);
            write(ans), puts("");
        }
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