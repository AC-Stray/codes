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
const int N = 300005;
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
        mutable ll val;
        odt_node(int l, int r = -1, ll val = 0): l(l), r(r), val(val) {}
        bool operator < (const odt_node &b) const { return l < b.l; }
    };
    set<odt_node> odt;
    vector<odt_node> tmp;
    set<odt_node>::iterator split(int pos){
        set<odt_node>::iterator iter = odt.lower_bound(odt_node(pos));
        if(iter != odt.end() && iter->l == pos) return iter;
        iter--;
        if(iter->r < pos) return odt.end();
        int l = iter->l, r = iter->r;
        ll val = iter->val;
        odt.erase(iter);
        odt.emplace(l, pos - 1, val);
        return odt.emplace(pos, r, val).first;
    }
    ll sum(int l, int r){
        set<odt_node>::iterator itr = split(r + 1), itl = split(l);
        ll res = 0;
        while(itl != itr) res = (res + (itl->r - itl->l + 1) * itl->val % MOD) % MOD, itl++;
        return res;
    }
    void assign(int l, int r, ll k){
        set<odt_node>::iterator itr = split(r + 1), itl = split(l);
        odt.erase(itl, itr);
        odt.emplace(l, r, k);
    }
    void add(int l, int r, ll k){
        set<odt_node>::iterator itr = split(r + 1), itl = split(l);
        while(itl != itr){
            itl->val = (itl->val + k) % MOD;
            itl++;
        }
    }
    void copy(int l1, int r1, int l2, int r2){
        set<odt_node>::iterator itr = split(r2 + 1), itl = split(l2);
        odt.erase(itl, itr);
        set<odt_node>::iterator iter = odt.lower_bound(odt_node(l1));
        if(iter == odt.end() || iter->l != l1) iter--;
        while(iter != odt.end() && iter->l <= r1){
            odt.emplace(max(iter->l,l1)-l1+l2, min(iter->r,r1)-r1+r2, iter->val);
            iter++;
        }
    }
    void swap(int l1, int r1, int l2, int r2){
        if(l1 > l2) std::swap(l1, l2), std::swap(r1, r2);
        set<odt_node>::iterator itr = split(r1 + 1), itl = split(l1);
        tmp.clear();
        for(set<odt_node>::iterator iter = itl; iter != itr; iter++) tmp.push_back(*iter);
        odt.erase(itl, itr);
        itr = split(r2 + 1), itl = split(l2);
        for(set<odt_node>::iterator iter = itl; iter != itr; iter++){
            odt.emplace(iter->l - l2 + l1, iter->r - r2 + r1, iter->val);
        }
        odt.erase(itl, itr);
        for(vector<odt_node>::iterator iter = tmp.begin(); iter != tmp.end(); iter++){
            odt.emplace(iter->l - l1 + l2, iter->r - r1 + r2, iter->val);
        }
    }
    void reverse(int l, int r){
        set<odt_node>::iterator itr = split(r + 1), itl = split(l);
        int len = r - l;
        tmp.clear();
        for(set<odt_node>::iterator iter = itl; iter != itr; iter++) tmp.push_back(*iter);
        odt.erase(itl, itr);
        reverse(tmp.begin(), tmp.end());
        for(vector<odt_node>::iterator iter = tmp.begin(); iter != tmp.end(); iter++){
            iter->l = l + len - iter->l + l;
            iter->r = l + len - iter->r + l;
            std::swap(iter->l, iter->r);
            odt.insert(*iter);
        }
    }
    int n, m, op, l, r, L, R, val;
    void Main(){
        input(n, m);
        for(ri i = 1; i <= n; i++) odt.emplace(i, i, read<ll>());
        while(m--){ 
            input(op);
            if(op == 1){
                input(l, r);
                write(sum(l, r)), puts("");
            }
            else if(op == 2){
                input(l, r, val);
                assign(l, r, val);
            }
            else if(op == 3){
                input(l, r, val);
                add(l, r, val);
            }
            else if(op == 4){
                input(l, r, L, R);
                copy(l, r, L, R);
            }
            else if(op == 5){
                input(l, r, L, R);
                swap(l, r, L, R);
            }
            else{
                input(l, r);
                reverse(l, r);
            }
            // for(set<odt_node>::iterator iter = odt.begin(); iter != odt.end(); iter++){
            //     for(ri i = iter->l; i <= iter->r; i++){
            //         write(iter->val), putchar(' ');
            //     }
            // } puts("");
        }
        for(set<odt_node>::iterator iter = odt.begin(); iter != odt.end(); iter++){
            for(ri i = iter->l; i <= iter->r; i++){
                write(iter->val), putchar(' ');
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