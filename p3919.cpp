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
    if(n<0) return putchar('-'), write(-n);
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
    const int N = 1000005;
    int n, m, a[N], ver[N];
    struct chairtree{
        int tot;
        struct chairtree_node{
            int l, r, ls, rs, val;
        }t[N<<5];
        int build(int l, int r){
            int p = ++tot;
            t[p].l = l, t[p].r = r;
            if(l == r){
                t[p].val = a[l];
                return p;
            }
            int mid = l + r >> 1;
            t[p].ls = build(l, mid);
            t[p].rs = build(mid + 1, r);
            return p;
        }
        int clone(int p){
            t[++tot] = t[p];
            return tot;
        }
        int modify(int p, int x, int k){
            p = clone(p);
            if(t[p].l == x && t[p].r == x){
                t[p].val = k;
                return p;
            }
            int mid = t[p].l + t[p].r >> 1;
            if(mid >= x) t[p].ls = modify(t[p].ls, x, k);
            else t[p].rs = modify(t[p].rs, x, k);
            return p;
        }
        int query(int p, int x){
            if(t[p].l == x && t[p].r == x) return t[p].val;
            int mid = t[p].l + t[p].r >> 1;
            if(mid >= x) return query(t[p].ls, x);
            else return query(t[p].rs, x);
        }
    }tree;
    void Main(){
        input(n, m);
        for(ri i = 1; i <= n; i++) input(a[i]);
        ver[0] = tree.build(1, n);
        for(ri i = 1; i <= m; i++){
            int t, op, k, val;
            input(t, op, k);
            if(op == 1){
                input(val);
                ver[i] = tree.modify(ver[t], k, val);
            }
            else{
                write(tree.query(ver[t], k));
                puts("");
                ver[i] = ver[t];
            }
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