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
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int N = 200005;
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
    int n, m, c[N], f[N];
    struct road{
        int l, r, p;
        bool operator < (const road &b) const { return r < b.r; }
    }r[N];
    struct segtree{
        struct segtree_node{
            int l, r, val, add;
        }t[N<<2];
        #define ls p<<1
        #define rs p<<1|1
        void pushup(int p){
            t[p].val = max(t[ls].val, t[rs].val);
        }
        void pushdown(int p){
            if(!t[p].add) return;
            t[ls].val += t[p].add, t[rs].val += t[p].add;
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
        void modify(int p, int l, int r, int k){
            if(t[p].l >= l && t[p].r <= r){
                t[p].val += k;
                t[p].add += k;
                return;
            }
            int mid = t[p].l + t[p].r >> 1;
            pushdown(p);
            if(mid >= l) modify(ls, l, r, k);
            if(mid < r)  modify(rs, l, r, k);
            pushup(p);
        }
        int query(int p, int l, int r){
            if(t[p].l >= l && t[p].r <= r) return t[p].val;
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
        input(n, m);
        for(ri i = 1; i <= n; i++) input(c[i]);
        for(ri i = 1; i <= m; i++) input(r[i].l, r[i].r, r[i].p);
        sort(r + 1, r + m + 1);
        tree.build(1, 0, n);
        for(ri i = 1, j = 1; i <= n; i++){
            while(r[j].r == i) tree.modify(1, 0, r[j].l - 1, r[j].p), j++;
            tree.modify(1, 0, i - 1, -c[i]);
            f[i] = max(f[i-1], tree.t[1].val);
            tree.modify(1, i, i, f[i]);
        }
        write(f[n]);
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