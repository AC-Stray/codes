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
    const double inf = 1e18;
    const int N= 300005;
    int n, m, a[N], b[N], ma[N], mb[N], q[N], head, tail;
    ll f[N];
    struct line{
        int u, v;
        line() {}
        line(int u, int v): u(u), v(v) {}
        bool operator < (const line &b) const { return u == b.u ? v > b.v : u < b.u; }
    }s[N];
    vector<line> p;
    Int X(int i) { return -ma[p[i+1].u-1]; }
    Int Y(int i) { return f[i]; }
    Int K(int i) { return mb[p[i].v+1]; }
    inline double slope(int i, int j){
        if(X(i) == X(j)) return inf;
        return (double)(Y(i) - Y(j)) / (X(i) - X(j));
    }
    void Main(){
        input(n, m);
        for(ri i = 1; i <= n; i++) input(a[i]);
        for(ri i = 1; i <= n; i++) input(b[i]);
        for(ri i = 1; i <= m; i++) input(s[i].u, s[i].v);
        sort(s + 1, s + m + 1);
        p.emplace_back(0, 0);
        for(ri i = 1; i <= m; i++){
            if(s[i].v < (p.end()-1)->v) continue;
            p.push_back(s[i]);
        }
        ma[0] = mb[n+1] = 1e9;
        for(ri i = 1; i <= n; i++) ma[i] = min(ma[i-1], a[i]);
        for(ri i = n; i >= 1; i--) mb[i] = min(mb[i+1], b[i]);
        for(ri i = 1; i < p.size(); i++){
            while(head < tail && slope(q[head], q[head+1]) <= K(i)) head++;
            // cerr << q[head] << ' ';
            f[i] = f[q[head]] + 1ll * ma[p[q[head]+1].u-1] * mb[p[i].v+1];
            while(head < tail && slope(q[tail-1], q[tail]) > slope(q[tail], i)) tail--;
            q[++tail] = i;
        }
        // cerr << endl;
        // for(ri i = 1; i < p.size(); i++) cerr << f[i] << ' '; cerr << endl;
        write(f[p.size()-1]);
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