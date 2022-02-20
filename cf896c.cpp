#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int MOD = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const int N = 100005;
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
    struct odt_node{
        int l, r;
        mutable ll v;
        odt_node(int l, int r = -1, ll v = 0): l(l), r(r), v(v) {}
        bool operator < (const odt_node &b) const { return l < b.l; }
    };
    set<odt_node> odt;
    set<odt_node>::iterator split(int pos){
        set<odt_node>::iterator iter = odt.lower_bound(odt_node(pos));
        if(iter != odt.end() && iter->l == pos) return iter;
        iter--;
        if(iter->r < pos) return odt.end();
        int l = iter->l, r = iter->r;
        ll v = iter->v;
        odt.erase(iter);
        odt.emplace(l, pos-1, v);
        return odt.emplace(pos, r, v).first;
    }
    void assign(int l, int r, ll val){
        set<odt_node>::iterator itr = split(r + 1), itl = split(l);
        odt.erase(itl, itr);
        odt.emplace(l, r, val);
    }
    void add(int l, int r, ll val){
        set<odt_node>::iterator itr = split(r + 1), itl = split(l);
        while(itl != itr) itl->v += val, itl++;
    }
    ll kth(int l, int r, int k){
        set<odt_node>::iterator itr = split(r + 1), itl = split(l);
        vector< pair<ll, int> > ran;
        while(itl != itr) ran.push_back(make_pair(itl->v, itl->r - itl->l + 1)), itl++;
        sort(ran.begin(), ran.end());
        for(vector< pair<ll, int> >::iterator iter = ran.begin(); iter != ran.end(); iter++){
            k -= iter->second;
            if(k <= 0) return iter->first;
        }
        return -1;
    }
    ll qpow(ll n, ll k, int mod){
        ll res = 1;
        n %= mod;
        while(k > 0){
            if(k & 1) res = res * n % mod;
            n = n * n % mod;
            k >>= 1;
        }
        return res;
    }
    ll rangePow(int l, int r, int x, int y){
        set<odt_node>::iterator itr = split(r + 1), itl = split(l);
        ll res = 0;
        while(itl != itr) res = (res + (itl->r-itl->l+1) * qpow(itl->v, x, y) % y) % y, itl++;
        return res;
    }
    ll n, m, seed, vmax, op, l, r, x, y;
    ll rnd(){
        ll res = seed;
        seed = (seed * 7 + 13) % MOD;
        return res;
    }
    void Main(){
        input(n, m, seed, vmax);
        for(ri i = 1; i <= n; i++) odt.emplace(i, i, rnd() % vmax + 1);
        for(ri i = 1; i <= m; i++){
            op = rnd() % 4 + 1;
            l = rnd() % n + 1;
            r = rnd() % n + 1;
            if(l > r) swap(l, r);
            if(op == 3) x = rnd() % (r - l + 1) + 1;
            else x = rnd() % vmax + 1;
            if(op == 4) y = rnd() % vmax + 1;
            if(op == 1) add(l, r, x);
            else if(op == 2) assign(l, r, x);
            else if(op == 3) write(kth(l, r, x)), puts("");
            else write(rangePow(l, r, x, y)), puts("");
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