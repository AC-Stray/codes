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
const int N = 35005;
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
    int n, k, a[N], f[N], pos[N], pre[N];
    struct segtree{
        struct segtree_node{
            int l, r, mx, add;
        }t[N<<2];
        #define ls p<<1
        #define rs p<<1|1
        void pushup(int p){
            t[p].mx = max(t[ls].mx, t[rs].mx);
        }
        void pushdown(int p){
            if(!t[p].add) return;
            t[ls].mx += t[p].add, t[rs].mx += t[p].add;
            t[ls].add += t[p].add, t[rs].add += t[p].add;
            t[p].add = 0;
        }
        void build(int p, int l, int r){
            t[p].l = l, t[p].r = r;
            if(t[p].l == t[p].r) return;
            int mid = l + r >> 1;
            build(ls, l, mid);
            build(rs, mid + 1, r);
        }
        void remake(int p){
            t[p].add = 0;
            if(t[p].l == t[p].r){
                t[p].mx = f[t[p].l];
                return;
            }
            remake(ls), remake(rs);
            pushup(p);
        }
        void modify(int p, int l, int r){
            if(t[p].l >= l && t[p].r <= r){
                t[p].mx++, t[p].add++;
                return;
            }
            int mid = t[p].l + t[p].r >> 1;
            pushdown(p);
            if(mid >= l) modify(ls, l, r);
            if(mid < r)  modify(rs, l, r);
            pushup(p);
        }
        int query(int p, int l, int r){
            if(t[p].l >= l && t[p].r <= r) return t[p].mx;
            int mid = t[p].l + t[p].r >> 1, res = 0;
            pushdown(p);
            if(mid >= l) res = max(res, query(ls, l, r));
            if(mid < r)  res = max(res, query(rs, l, r));
            return res;
        }
        #undef ls
        #undef rs
    }tree;
    void Main(){
        input(n, k);
        for(ri i = 1; i <= n; i++) input(a[i]), pre[i] = pos[a[i]], pos[a[i]] = i;
        tree.build(1, 0, n);
        for(ri i = 1; i <= k; i++){
            tree.remake(1);
            for(ri j = 1; j <= n; j++){
                tree.modify(1, pre[j], j - 1);
                f[j] = tree.query(1, 0, j - 1);
                // cerr << f[j] << ' ';
            }
            // cerr << endl;
        }
        write(f[n]);
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