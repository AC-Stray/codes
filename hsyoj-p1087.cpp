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
const int N = 1000005;
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
    int n, a[N], pre[N][3];
    ll ans;
    struct segtree{
        struct segtree_node{
            int l, r, val, tag;
        }t[N<<3];
        #define ls p<<1
        #define rs p<<1|1
        void pushup(int p){
            if(t[p].tag > 0) t[p].val = t[p].r - t[p].l + 1;
            else t[p].val = t[ls].val + t[rs].val;
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
                t[p].tag += k;
                pushup(p);
                return;
            }
            int mid = t[p].l + t[p].r >> 1;
            if(mid >= l) modify(ls, l, r, k);
            if(mid < r)  modify(rs, l, r, k);
            pushup(p);
        }
        #undef ls
        #undef rs
    }tree;
    void Main(){
        input(n);
        for(ri i = 1; i <= n; i++) input(a[i]);
        tree.build(1, 1, n);
        for(ri i = 1; i <= n; i++){
            tree.modify(1, 1, pre[a[i]][2], -1);
            tree.modify(1, pre[a[i]][1] + 1, pre[a[i]][0], -1);
            pre[a[i]][2] = pre[a[i]][1], pre[a[i]][1] = pre[a[i]][0], pre[a[i]][0] = i;
            tree.modify(1, 1, pre[a[i]][2], 1);
            tree.modify(1, pre[a[i]][1] + 1, pre[a[i]][0], 1);
            ans += i - tree.t[1].val;
            // cerr << ans << endl;
        }
        write(ans);
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
