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
struct node{
    int a, b, k;
}nds[1000005];
int t, n, m[2000005];
int fa[1000005];
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
Bool cmp(node a, node b) { return a.k > b.k; }
int get(int a){
    if(fa[a] == a) return a;
    return fa[a] = get(fa[a]);
}
Void unite(int a, int b){
    fa[get(a)] = get(b);
}
int main(){
    input(t);
    start:while(t--){
        input(n);
        for(ri i = 0; i < n; i++){
            input(nds[i].a, nds[i].b, nds[i].k);
            m[2*i] = nds[i].a, m[2*i+1] = nds[i].b;
        }
        sort(nds, nds+n, cmp);
        sort(m, m+2*n);
        int len = unique(m, m+2*n) - m;
        for(ri i = 0; i < n; i++){
            nds[i].a = lower_bound(m, m+len, nds[i].a) - m;
            nds[i].b = lower_bound(m, m+len, nds[i].b) - m;
        }
        for(ri i = 0; i <= len; i++) fa[i] = i;
        for(ri i = 0; i < n; i++){
            if(nds[i].k == 1) unite(nds[i].a, nds[i].b);
            else{
                if(get(nds[i].a) == get(nds[i].b)){
                    puts("NO");
                    goto start;
                }
            }
        }
        puts("YES");
    }
	return 0;
}