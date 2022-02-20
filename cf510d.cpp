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
    const int inf = 0x7fffffff;
    const int N = 305;
    int n, l[N], c[N];
    map<int, bool> vis;
    map<int, int> dst;
    struct node{
        int v, w;
        node() {}
        node(int v, int w): v(v), w(w) {}
        bool operator < (const node &b) const { return w > b.w; }
    };
    void dijkstra(){
        priority_queue<node> q;
        q.emplace(0, 0);
        dst[0] = 0;
        while(!q.empty()){
            node now = q.top(); q.pop();
            if(now.v == 1) break;
            if(vis.find(now.v) != vis.end()) continue;
            for(ri i = 0; i < n; i++){
                int v = __gcd(now.v, l[i]);
                if(dst.find(v) == dst.end()) dst[v] = inf;
                if(dst[v] > now.w + c[i]){
                    dst[v] = now.w + c[i];
                    q.emplace(v, dst[v]);
                }
            }
        }
    }
    void Main(){
        input(n);
        for(ri i = 0; i < n; i++) input(l[i]);
        for(ri i = 0; i < n; i++) input(c[i]);
        dijkstra();
        if(dst.find(1) == dst.end()) puts("-1");
        else write(dst[1]);
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