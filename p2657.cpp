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
int a, b, f[20][10];
vector<int> split;
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
int dfs(int x, int lst, int op){
    if(x == 0) return 1;
    // if(!op && f[x][lst]) return f[x][lst];
    int mx = op ? split[x-1] : 9, rt = 0;
    for(ri i = 0; i <= mx; i++){
        if(abs(i-lst) < 2) continue;
        if(lst == 20 && i == 0) rt += dfs(x-1, 20, op & (i==mx));
        else rt += dfs(x-1, i, op & (i==mx));
    }
    if(!op) f[x][lst] = rt;
    return rt;
}
Int ans(int n){
    memset(f, 0, sizeof(f));
    split.clear();
    while(n > 0){
        split.push_back(n%10);
        n /= 10;
    }
    return dfs(split.size(), 20, 1);
}
int main(){
    input(a, b);
    write(ans(b)-ans(a-1));
	return 0;
}