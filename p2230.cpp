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
int n, k, p[2005], memory[2005][2005];
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
int dfs(int x, int y){
	if(x == 1) return memory[1][y] = p[y];
	if(y == k) return memory[x][k] = dfs(x, 1) + p[k]*x*x;
	if(memory[x][y]) return memory[x][y];
	memory[x][y] = dfs(x-1, y+1) + p[y];
	for(ri i = 2; i < x; i++) memory[x][y] = min(memory[x][y], dfs(x-i, y+1) + dfs(i, 1) + p[y]*i*i);
	return memory[x][y];
}
int main(){
    input(n, k);
    for(ri i = 1; i <= k; i++) input(p[i]);
    sort(p+1, p+k+1);
    write(dfs(n, 1));
	return 0;
}