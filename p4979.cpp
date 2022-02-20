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
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int N = 500005;
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
    int n, k;
    char s[N];
    struct odt_node{
        int l, r, val;
        odt_node(int l, int r = -1, int val = 0): l(l), r(r), val(val) {}
        bool operator < (const odt_node &b) const { return l < b.l; }
    };
    set<odt_node> odt;
    set<odt_node>::iterator split(int pos){
        set<odt_node>::iterator iter = odt.lower_bound(odt_node(pos));
        if(iter != odt.end() && iter->l == pos) return iter;
        iter--;
        if(iter->r < pos) return odt.end();
        int l = iter->l, r = iter->r, val = iter->val;
        odt.erase(iter);
        odt.emplace(l, pos - 1, val);
        return odt.emplace(pos, r, val).first;
    }
    void assign(int l, int r, int val){
        set<odt_node>::iterator itr = split(r + 1), itl = split(l);
        odt.erase(itl, itr);
        odt.emplace(l, r, val);
    }
    bool query(int l, int r){
        set<odt_node>::iterator itr = split(r + 1), itl = split(l);
        if(l != 1 && r != n){
            itl--;
            if(itl->val == itr->val) return false;
            itl++;
        }
        int L = itl->l, R = itl->r, val = itl->val;
        set<odt_node>::iterator it = itl;
        it++;
        while(it != itr){
            if(it->val != itl->val){
                odt.erase(itl, it);
                odt.emplace(L, R, val);
                return false;
            }
            R = it->r;
            it++;
        }
        odt.erase(itl, itr);
        odt.emplace(L, R, val);
        return true;
    }
    int toint(char ch){
        switch(ch){
            case 'A': return 0; 
            case 'B': return 1;
            case 'C': return 2;
            default:  return -1;
        }
    }
    char readch(){
        char ch = getchar();
        while(ch < 'A' || ch > 'C') ch = getchar();
        return ch;
    }
    void Main(){
        input(n);
        scanf("%s", s + 1);
        for(ri i = 1; i <= n; i++) odt.emplace(i, i, toint(s[i]));
        input(k);
        while(k--){
            char op;
            int x, y;
            op = readch();
            input(x, y);
            if(op == 'A'){
                op = readch();
                assign(x, y, toint(op));
            }
            else puts(query(x, y) ? "Yes" : "No");
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