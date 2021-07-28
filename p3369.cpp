#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
LL read(){
    ll n = 0; int f = 1; char ch = getchar();
    while('0' > ch || ch > '9'){
        if(ch == '-') f *= -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9'){
        n = (n << 1) + (n << 3) + ch-'0';
        ch = getchar();
    }
    return f * n;
}
Void write(ll x){
    if(x/10) write(x/10);
    putchar(x%10+'0');
}
Void input() {}
template<typename Type, typename... Types>
Void input(Type& arg, Types&... args){
    arg = read();
    input(args...);
}
int n, opt, v;
namespace Splay{
    const int SIZE = 100005;
    int root, tot, fa[SIZE], ch[SIZE][2], v[SIZE], cnt[SIZE], sz[SIZE];
    Void maintain(int x){
        sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + cnt[x];
    }
    Bool get(int x){
        return x == ch[fa[x]][1];
    }
    Void clear(int x){
        ch[x][0] = ch[x][1] = fa[x] = v[x] = sz[x] = cnt[x] = 0;
    }
    Void rotate(int x){
        bool flag = get(x);
        int y = fa[x], z = fa[y];
        ch[y][flag] = ch[x][flag^1];
        if(ch[x][flag^1]) fa[ch[x][flag^1]] = y;
        ch[x][flag^1] = y;
        fa[y] = x;
        fa[x] = z;
        if(z) ch[z][y==ch[z][1]] = x;
        maintain(x);
        maintain(y);
    }
    Void splay(int x){
        for(ri i = fa[x]; i = fa[x], i; rotate(x)){
            if(fa[i]) rotate(get(x)==get(i)?i:x);
        }
        root = x;
    }
    Void insert(int x){
        if(!root){
            v[++tot] = x;
            cnt[tot]++;
            root = tot;
            maintain(tot);
            return;
        }
        int now = root, lst = 0;
        while(true){
            if(v[now] == x){
                cnt[now]++;
                maintain(now);
                maintain(lst);
                splay(now);
                break;
            }
            lst = now;
            now = ch[now][v[now]<x];
            if(!now){
                v[++tot] = x;
                cnt[tot]++;
                fa[tot] = lst;
                ch[lst][v[lst]<x] = tot;
                maintain(tot);
                maintain(lst);
                splay(tot);
                break;
            }
        }
    }
    Int rank(int x){
        int res = 0, now = root;
        while(true){
            if(x < v[now]) now = ch[now][0];
            else{
                res += sz[ch[now][0]];
                if(x == v[now]){
                    splay(now);
                    return res + 1;
                }
                res += cnt[now];
                now = ch[now][1];
            }
        }
    }
    Int query(int x){
        int now = root;
        while(true){
            if(ch[now][0] && x <= sz[ch[now][0]]) now = ch[now][0];
            else{
                x -= cnt[now] + sz[ch[now][0]];
                if(x <= 0){
                    splay(now);
                    return v[now];
                }
                now = ch[now][1];
            }
        }
    }
    Int pre(){
        int now = ch[root][0];
        while(ch[now][1]) now = ch[now][1];
        splay(now);
        return now;
    }
    Int nxt(){
        int now = ch[root][1];
        while(ch[now][0]) now = ch[now][0];
        splay(now);
        return now;
    }
    Void del(int x){
        rank(x);
        if(cnt[root] > 1){
            cnt[root]--;
            maintain(root);
            return;
        }
        if(!ch[root][0] && !ch[root][1]){
            clear(root);
            root = 0;
            return;
        }
        if(!ch[root][0]){
            int now = root;
            root = ch[root][1];
            fa[root] = 0;
            clear(now);
            return;
        }
        if(!ch[root][1]){
            int now = root;
            root = ch[root][0];
            fa[root] = 0;
            clear(now);
            return;
        }
        int now = root, y = pre();
        fa[ch[now][1]] = y;
        ch[y][1] = ch[now][1];
        clear(now);
        maintain(root);
    }
}
int main(){
    input(n);
    while(n--){
        input(opt, v);
        switch(opt){
            case 1: Splay::insert(v); break;
            case 2: Splay::del(v); break;
            case 3: cout << Splay::rank(v) << endl; break;
            case 4: cout << Splay::query(v) << endl; break;
            case 5: Splay::insert(v); cout << Splay::v[Splay::pre()] << endl; Splay::del(v); break;
            case 6: Splay::insert(v); cout << Splay::v[Splay::nxt()] << endl; Splay::del(v); break;
        }
    }
    return 0;
}