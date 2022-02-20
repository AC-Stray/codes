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
    const unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 my_rand(seed);
    struct fhq_treap{
        int tot, root, ls[N], rs[N], siz[N], pri[N], val[N];
        bool rev[N];
        int alloc(int x) { siz[++tot] = 1, val[tot] = x, pri[tot] = my_rand(); return tot; }
        void pushup(int x) { siz[x] = siz[ls[x]] + siz[rs[x]] + 1; }
        void pushrev(int x) { if(x) rev[x] ^= 1; }
        void pushdown(int x){
            if(!rev[x]) return;
            swap(ls[x], rs[x]);
            pushrev(ls[x]), pushrev(rs[x]);
            rev[x] = false;
        }
        void split(int x, int k, int &L, int &R){
            if(x == 0) return L = R = 0, void();
            pushdown(x);
            if(siz[ls[x]] >= k) R = x, split(ls[x], k, L, ls[x]);
            else L = x, split(rs[x], k - siz[ls[x]] - 1, rs[x], R);
            pushup(x);
        }
        int merge(int x, int y){
            if(!x || !y) return x | y;
            if(pri[x] > pri[y]) return pushdown(x), rs[x] = merge(rs[x], y), pushup(x), x;
            else return pushdown(y), ls[y] = merge(x, ls[y]), pushup(y), y;
        }
        void reverse(int l, int r){
            int L, R, R0;
            split(root, r, L, R);
            split(L, l - 1, L, R0);
            pushrev(R0);
            root = merge(L, merge(R0, R));
        }
        void dfs(int u){
            if(!u) return;
            pushdown(u);
            dfs(ls[u]);
            write(val[u]), putchar(' ');
            dfs(rs[u]);
        }
    }tree;
    int n, m;
    void Main(){
        input(n, m);
        for(ri i = 1; i <= n; i++) tree.root = tree.merge(tree.root, tree.alloc(i));
        while(m--){
            int l, r;
            input(l, r);
            tree.reverse(l, r);
        }
        tree.dfs(tree.root);
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