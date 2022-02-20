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
    const int N = 50005;
    int n, m, MOD, q, s[N];
    struct matrix{
        int v[2][2];
        matrix() {}
        matrix(int a, int b, int c, int d){
            v[0][0] = a, v[0][1] = b;
            v[1][0] = c, v[1][1] = d;
        }
        const int* operator [] (const int &index) const {
            return v[index];
        }
        int* operator [] (const int &index){
            return v[index];
        }
        matrix operator * (const matrix &b) const {
            matrix res(0, 0, 0, 0);
            for(int i = 0; i < 2; i++){
                for(int k = 0; k < 2; k++){
                    for(int j = 0; j < 2; j++){
                        res[i][j] = (res[i][j] + v[i][k] * b[k][j] % MOD) % MOD;
                    }
                }
            }
            return res;
        }
        void print(){
            fprintf(stdout, "%lld %lld\n%lld %lld\n\n", v[0][0], v[0][1], v[1][0], v[1][1]);
        }
    }ans(1, 0, 0, 1), S;
    struct segtree{
        struct segtree_node{
            int l, r;
            matrix val;
        }t[N<<2];
        #define ls (p<<1)
        #define rs (p<<1|1)
        void pushup(int p) { t[p].val = t[ls].val * t[rs].val; }
        void build(int p, int l, int r){
            t[p].l = l, t[p].r = r;
            if(t[p].l == t[p].r){
                t[p].val = matrix(0, s[l], 1, s[(l+1)%n]);
                return;
            }
            int mid = l + r >> 1;
            build(ls, l, mid);
            build(rs, mid + 1, r);
            pushup(p);
        }
        matrix query(int p, int l, int r){
            if(t[p].l >= l && t[p].r <= r) return t[p].val;
            int mid = t[p].l + t[p].r >> 1;
            matrix res(1, 0, 0, 1);
            if(mid >= l) res = res * query(ls, l, r);
            if(mid < r)  res = res * query(rs, l, r);
            return res;
        }
        #undef ls
        #undef rs
    }tree;
    map<int, matrix> mp;
    matrix qpow(matrix n, int k){
        matrix res(1, 0, 0, 1);
        while(k > 0){
            if(k & 1) res = res * n;
            n = n * n;
            k >>= 1;
        }
        return res;
    }
    void solve(int l, int r){
        if(l > r) return;
        int bl = l / n, br = r / n;
        l %= n, r %= n;
        if(bl == br) ans = ans * tree.query(1, l, r);
        else{
            ans = ans * tree.query(1, l, n - 1);
            ans = ans * qpow(S, br - bl - 1) * tree.query(1, 0, r);
        }
    }
    void modify(int p, int x, int k){
        if(mp.count(p) == 0) mp[p] = matrix(0, s[p%n], 1, s[(p+1)%n]);
        mp[p][x][1] = k;
    }
    void Main(){
        input(m, MOD, n);
		if(m == 0) return puts("0"), void();
		if(m == 1) return write(1 % MOD), void();
		m -= 2;
        for(int i = 0; i < n; i++) input(s[i]);
        input(q);
        for(int i = 0, x, y; i < q; i++){
        	input(x, y);
            modify(x - 1, 1, y);
            modify(x, 0, y);
        }
        tree.build(1, 0, n - 1);
        S = tree.query(1, 0, n - 1);
        int lst = 0;
        for(map<int, matrix>::iterator iter = mp.begin(); iter != mp.end(); iter++){
            if(iter->first > m) break;
            solve(lst, iter->first - 1);
            ans = ans * iter->second;
            lst = iter->first + 1;
        }
        solve(lst, m);
        write(ans[1][1]);
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
