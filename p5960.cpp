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
    if(n < 0) return putchar('-'), write(-n);
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
    const int N = 5005;
    int n, m, deg[N], dst[N], cnt[N];
    bool inqueue[N];
    struct node{
        int v, w;
        node() {}
        node(int v, int w): v(v), w(w) {}
    };
    vector<node> g[N];
    bool spfa(){
        queue<int> q;
        memset(dst, 0x3f, sizeof(dst));
        q.push(0); dst[0] = 0;
        while(!q.empty()){
            int now = q.front(); q.pop();
            inqueue[now] = false;
            for(ri i = 0; i < g[now].size(); i++){
                node v = g[now][i];
                if(dst[now] + v.w < dst[v.v]){
                    dst[v.v] = dst[now] + v.w;
                    if(!inqueue[v.v]){
                        q.push(v.v);
                        inqueue[v.v] = true;
                        if(++cnt[v.v] >= n + 1) return false;
                    }
                }
            }
        }
        return true;
    }
    void Main(){
        input(n, m);
        for(ri i = 0, c1, c2, y; i < m; i++){
            input(c1, c2, y);
            g[c2].emplace_back(c1, y);
            deg[c1]++;
        }
        for(ri i = 1; i <= n; i++) g[0].emplace_back(i, 0);
        if(!spfa()) puts("NO");
        else for(ri i = 1; i <= n; i++) write(dst[i]), putchar(' ');
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