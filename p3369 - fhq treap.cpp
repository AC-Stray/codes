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
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++)
char buf[1000000], *p1(buf), *p2(buf);
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
    const unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 my_rand(seed);
    struct fhq_treap{
        int tot, root, ls[N], rs[N], pri[N], val[N], siz[N];
        int alloc(int x) { siz[++tot] = 1, pri[tot] = my_rand(), val[tot] = x; return tot; }
        void pushup(int x) { siz[x] = siz[ls[x]] + siz[rs[x]] + 1; }
        // 让以 x 为根的 Treap 裂开，小于等于 k 的分左边，大于 k 的分右边
        // L 和 R 最终会是左右子树的根节点
        void split(int x, int k, int &L, int &R){
            if(x == 0) return L = R = 0, void();
            if(val[x] <= k) L = x, split(rs[x], k, rs[x], R), pushup(x);
            else R = x, split(ls[x], k, L, ls[x]), pushup(x);
        }
        // 合并以 x 和 y 为根的两个 Treap
        // merge 的前提是 x 整体小于等于 y
        // 按照随出来的优先级合并，保证优先级高的在上面
        // 返回合并后的根
        int merge(int x, int y){
            if(!x || !y) return x | y;
            if(pri[x] > pri[y]) return rs[x] = merge(rs[x], y), pushup(x), x;
            else return ls[y] = merge(x, ls[y]), pushup(y), y;
        }
        void insert(int x){
            int L, R;
            split(root, x, L, R);
            root = merge(L, merge(alloc(x), R));
        }
        void erase(int x){
            int L, R0, R;
            split(root, x, L, R);
            split(L, x - 1, L, R0);
            R0 = merge(ls[R0], rs[R0]);
            root = merge(L, merge(R0, R));
        }
        int rank(int x){
            int L, R;
            split(root, x - 1, L, R);
            int res = siz[L] + 1;
            root = merge(L, R);
            return res;
        }
        int kth(int x, int k){
            while(true){
                if(k == siz[ls[x]] + 1) return x;
                if(k <= siz[ls[x]]) x = ls[x];
                else k -= siz[ls[x]] + 1, x = rs[x];
            }
        }
        int pre(int x){
            int L, R;
            split(root, x - 1, L, R);
            int res = val[kth(L, siz[L])];
            root = merge(L, R);
            return res;
        }
        int suf(int x){
            int L, R;
            split(root, x, L, R);
            int res = val[kth(R, 1)];
            root = merge(L, R);
            return res;
        }
    }tree;
    int n;
    void Main(){
        input(n);
        while(n--){
            int opt, x;
            input(opt, x);
            switch(opt){
                case 1: tree.insert(x); break;
                case 2: tree.erase(x); break;
                case 3: write(tree.rank(x)); puts(""); break;
                case 4: write(tree.val[tree.kth(tree.root, x)]); puts(""); break;
                case 5: write(tree.pre(x)); puts(""); break;
                case 6: write(tree.suf(x)); puts(""); break;
            }
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