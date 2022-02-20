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
    const int N = 200005;
    int n, m, a[N], num[N], root[N];
    struct chairtree{
        int tot;
        struct chairtree_node{
            int l, r, ls, rs, val;
        }t[N<<5];
        void pushup(int p) { t[p].val = t[t[p].ls].val + t[t[p].rs].val; }
        int build(int l, int r){
            int p = ++tot;
            t[p].l = l, t[p].r = r;
            if(l == r) return p;
            int mid = l + r >> 1;
            t[p].ls = build(l, mid);
            t[p].rs = build(mid + 1, r);
            pushup(p);
            return p;
        }
        int clone(int p){
            t[++tot] = t[p];
            return tot;
        }
        int modify(int p, int x){
            p = clone(p);
            if(t[p].l == x && t[p].r == x){
                t[p].val++;
                return p;
            }
            int mid = t[p].l + t[p].r >> 1;
            if(mid >= x) t[p].ls = modify(t[p].ls, x);
            else t[p].rs = modify(t[p].rs, x);
            pushup(p);
            return p;
        }
        int query(int u, int v, int k){
            int sub = t[t[v].ls].val - t[t[u].ls].val;
            if(t[u].l == t[u].r) return t[u].l;
            if(k <= sub) return query(t[u].ls, t[v].ls, k);
            else return query(t[u].rs, t[v].rs, k - sub);
        }
    }tree;
    void Main(){
        input(n, m);
        for(ri i = 1; i <= n; i++) input(a[i]), num[i] = a[i];
        sort(num + 1, num + n + 1);
        int k = unique(num + 1, num + n + 1) - num - 1;
        for(ri i = 1; i <= n; i++) a[i] = lower_bound(num + 1, num + k + 1, a[i]) - num;
        root[0] = tree.build(1, k);
        for(ri i = 1; i <= n; i++) root[i] = tree.modify(root[i-1], a[i]);
        while(m--){
            int l, r, k;
            input(l, r, k);
            write(num[tree.query(root[l-1], root[r], k)]);
            puts("");
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