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
    const int N = 500005;
    const unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    mt19937 my_rand(seed);
    struct fhqtreap{
        int tot, root, val[N], siz[N], ls[N], rs[N], sum[N], lmx[N], rmx[N], tmx[N], pri[N], cov[N];
        bool rev[N], flg[N];
        stack<int> rub;
        void init() { tmx[0] = -1e9; }
        int alloc(int x){
            int tmp;
            if(!rub.empty()) tmp = rub.top(), rub.pop();
            else tmp = ++tot;
            ls[tmp] = rs[tmp] = rev[tmp] = flg[tmp] = 0;
            siz[tmp] = 1;
            val[tmp] = x;
            lmx[tmp] = rmx[tmp] = max(0, x);
            tmx[tmp] = x;
            sum[tmp] = x;
            pri[tmp] = my_rand();
            return tmp;
        }
        void collect(int x){
            if(!x) return;
            rub.push(x);
            collect(ls[x]), collect(rs[x]);
            return;
        }
        void pushup(int x){
            siz[x] = siz[ls[x]] + siz[rs[x]] + 1;
            sum[x] = sum[ls[x]] + sum[rs[x]] + val[x];
            lmx[x] = max(max(lmx[ls[x]], sum[ls[x]] + val[x] + lmx[rs[x]]), 0);
            rmx[x] = max(max(rmx[rs[x]], sum[rs[x]] + val[x] + rmx[ls[x]]), 0);
            tmx[x] = max(max(tmx[ls[x]], tmx[rs[x]]), rmx[ls[x]] + val[x] + lmx[rs[x]]);
        }
        void pushre(int x) { if(x) rev[x] ^= 1, swap(ls[x], rs[x]), swap(lmx[x], rmx[x]); }
        void pushco(int x, int k){
            if(!x) return;
            flg[x] = true;
            val[x] = cov[x] = k;
            sum[x] = siz[x] * k;
            tmx[x] = max(k, sum[x]);
            lmx[x] = rmx[x] = max(sum[x], 0);
        }
        void pushdown(int x){
            if(rev[x]){
                pushre(ls[x]), pushre(rs[x]);
                rev[x] = false;
            }
            if(flg[x]){
                pushco(ls[x], cov[x]), pushco(rs[x], cov[x]);
                flg[x] = false;
            }
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
        void insert(int x, vector<int> c){
            int L, R;
            split(root, x, L, R);
            for(ri i = 0; i < c.size(); i++) L = merge(L, alloc(c[i]));
            root = merge(L, R);
        }
        void erase(int x, int len){
            int L, R, R0;
            split(root, x + len - 1, L, R);
            split(L, x - 1, L, R0);
            root = merge(L, R);
            collect(R0);
        }
        void modify(int x, int len, int k){
            int L, R, R0;
            split(root, x + len - 1, L, R);
            split(L, x - 1, L, R0);
            pushco(R0, k);
            root = merge(L, merge(R0, R));
        }
        void reverse(int x, int len){
            int L, R, R0;
            split(root, x + len - 1, L, R);
            split(L, x - 1, L, R0);
            pushre(R0);
            root = merge(L, merge(R0, R));
        }
        int querysum(int x, int len){
            int L, R, R0;
            split(root, x + len - 1, L, R);
            split(L, x - 1, L, R0);
            int res = sum[R0];
            root = merge(L, merge(R0, R));
            return res;
        }
        int mxsum() { return tmx[root]; }
        void __debug_print(int u){
            if(!u) return;
            pushdown(u);
            __debug_print(ls[u]);
            write(val[u]), putchar(' ');
            __debug_print(rs[u]);
            pushup(u);
        }
    }tree;
    int n, m;
    void Main(){
        input(n, m);
        tree.init();
        for(ri i = 0, tmp; i < n; i++){
            input(tmp);
            tree.root = tree.merge(tree.root, tree.alloc(tmp));
        }
        // tree.__debug_print(tree.root); puts("");
        while(m--){
            string op;
            cin >> op;
            if(op == "INSERT"){
                int p, len;
                vector<int> c;
                input(p, len);
                for(ri i = 0; i < len; i++) c.push_back(read<int>());
                tree.insert(p, c);
            }
            else if(op == "DELETE"){
                int p, len;
                input(p, len);
                tree.erase(p, len);
            }
            else if(op == "MAKE-SAME"){
                int p, len, k;
                input(p, len, k);
                tree.modify(p, len, k);
            }
            else if(op == "REVERSE"){
                int p, len;
                input(p, len);
                tree.reverse(p, len);
            }
            else if(op == "GET-SUM"){
                int p, len;
                input(p, len);
                write(tree.querysum(p, len));
                puts("");
            }
            else if(op == "MAX-SUM"){
                write(tree.mxsum());
                puts("");
            }
            else puts("FAQ");
            // tree.__debug_print(tree.root); puts("");
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