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
int n, m;
double s[2], nodes[10005];
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
int main(){
    input(n, m);
    for(ri i = 1; i <= n; i++) input(nodes[i]);
    for(ri i = 0; i < m; i++){
        int u, v, w;
        input(u, v, w);
        nodes[u] += w / 2.0;
        nodes[v] += w / 2.0;
    }
    sort(nodes+1, nodes+n+1);
    for(ri i = 1; i <= n; i++) s[i%2] += nodes[i];
    write(s[0] - s[1]);
	return 0;
}