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
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const double eps = 1e-12;
const int N = 100005;
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
    int n, k, head, tail, q[N];
    long double f[N], g[N];
    inline long double slope(int x, int y){
        return (f[x] - f[y]) / (x - y);
    }
    bool check(long double mid){
        head = tail = 0;
        q[head] = 0;
        for(ri i = 1; i <= n; i++){
            while(head < tail && slope(q[head], q[head+1]) > (long double)1 / i + eps) head++;
            f[i] = f[q[head]] + (long double)(i - q[head]) / i - mid;
            g[i] = g[q[head]] + 1;
            while(head < tail && slope(i, q[tail]) > slope(q[tail], q[tail-1]) + eps) tail--;
            q[++tail] = i;
        }
        return g[n] >= k;
    }
    void Main(){
        input(n, k);
        long double l = 0, r = 1;
        while(r - l > eps){
            long double mid = (l + r) / 2;
            if(check(mid)) l = mid;
            else r = mid;
        }
        cerr << l << endl;
        check(l);
        cout << fixed << setprecision(9) << f[n] + k * l;
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