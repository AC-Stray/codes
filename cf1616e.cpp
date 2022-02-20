#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define int long long
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
    const int N = 200005;
    const int V = 26;
    const int inf = 1e11;
    int q, n, ans, tot;
    char s[N], t[N];
    vector<int> pos[V];
    struct bit{
        int a[N];
        Int lowbit(int x) {  return x & -x; }
        void init() { memset(a, 0, sizeof(a)); }
        void add(int x, int k) { for(; x < N; x += lowbit(x)) a[x] += k; }
        int query(int x) { int res = 0; for(; x > 0; x -= lowbit(x)) res += a[x]; return res; }
    }tree;
    void Main(){
        input(q);
        while(q--){
            tree.init();
            for(int i = 0; i < V; i++) pos[i].clear();
            input(n);
            scanf("%s %s", s + 1, t + 1);
            for(int i = n; i > 0; i--) pos[s[i]-'a'].push_back(i);
            ans = inf, tot = 0;
            for(int i = 1; i <= n; i++){
                int step = inf;
                for(int j = 0; j < t[i] - 'a'; j++){
                    if(pos[j].empty()) continue;
                    int tmp = pos[j].back();
                    step = min(step, tmp - tree.query(tmp) - 1);
                }
                ans = min(ans, tot + step);
                if(pos[t[i]-'a'].empty()) break;
                int tmp = pos[t[i]-'a'].back();
                pos[t[i]-'a'].pop_back();
                tot += tmp - tree.query(tmp) - 1;
                tree.add(tmp, 1);
            }
            if(ans == inf) puts("-1");
            else write(ans), puts("");
        }
        return;
    }
} // namespace
signed main(){
#ifdef Liuxizai
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif // Liuxizai
    Main::Main();
    return 0;
}
