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
    const unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 my_rand(seed);
    struct fhqtreap{
        int tot, root, pri[N], fa[N], ls[N], rs[N], val[N], siz[N], bts[N];
        bool rev[N], del[N];
        int alloc(int x){
            siz[++tot] = 1;
            pri[tot] = my_rand();
            val[tot] = x;
            bts[tot] = 1 << x;
            return tot;
        }
        void pushup(int x){
            if(ls[x]) fa[ls[x]] = x;
            if(rs[x]) fa[rs[x]] = x;
            siz[x] = siz[ls[x]] + siz[rs[x]] + 1;
            bts[x] = bts[ls[x]] | bts[rs[x]] | (1 << val[x]);
        }
        void pushre(int x) { if(x) rev[x] ^= 1; }
        void pushdown(int x){
            if(!rev[x]) return;
            swap(ls[x], rs[x]);
            pushre(ls[x]), pushre(rs[x]);
            rev[x] = false;
        }
        void split(int x, int k, int &L, int &R){
            if(!x) return L = R = 0, void();
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
            pushre(R0);
            root = merge(L, merge(R0, R));
        }
        void insert(int x, int k){
            int L, R;
            split(root, x, L, R);
            root = merge(L, merge(alloc(k), R));
        }
        void erase(int x){
            int L, R, R0;
            split(root, x, L, R);
            split(L, x - 1, L, R0);
            del[R0] = true;
            root = merge(L, R);
        }
        int kth(int k){
            int L, R, R0;
            split(root, k, L, R);
            split(L, k - 1, L, R0);
            int res = val[R0];
            root = merge(L, merge(R0, R));
            return res;
        }
        int find(int x){
            if(del[x]) return 0;
            stack<int> stk;
            int tmp = x;
            while(tmp) stk.push(tmp), tmp = fa[tmp];
            while(!stk.empty()) pushdown(stk.top()), stk.pop();
            int res = siz[ls[x]] + 1;
            for(; fa[x]; x = fa[x]){
                if(rs[fa[x]] == x) res += siz[ls[fa[x]]] + 1;
            }
            return res;
        }
        int count(int l, int r){
            int L, R, R0;
            split(root, r, L, R);
            split(L, l - 1, L, R0);
            int res = __builtin_popcount(bts[R0]);
            root = merge(L, merge(R0, R));
            return res;
        }
        void __debug_print(int u){
            if(!u) return;
            pushdown(u);
            __debug_print(ls[u]);
            putchar(val[u] + 'a');
            __debug_print(rs[u]);
        }
    }tree;
    int n, m;
    char s[N];
    void Main(){
        input(n, m);
        scanf("%s", s);
        for(ri i = 0; i < n; i++)
        tree.root = tree.merge(tree.root, tree.alloc(s[i] - 'a'));
        // tree.__debug_print(tree.root); puts(""); fflush(stdout);
        while(m--){
            int x, y;
            char c, op;
            cin >> op;
            switch(op){
                case 'I': input(x), cin >> c; tree.insert(x, c - 'a'); break;
                case 'D': input(x); tree.erase(x); break;
                case 'R': input(x, y); tree.reverse(x, y); break;
                case 'P': input(x); write(tree.find(x)); puts(""); break;
                case 'T': input(x); putchar(tree.kth(x) + 'a'); puts(""); break;
                case 'Q': input(x, y); write(tree.count(x, y)); puts(""); break;
            }
            // tree.__debug_print(tree.root); puts(""); fflush(stdout);
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