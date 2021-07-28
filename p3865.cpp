#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<vector>
#include<set>
#include<queue>
#include<map>
#include<list>
#include<deque>
#include<cctype>
#include<climits>
#include<cmath>
#include<ctime>
#include<algorithm>
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
int n, m, l, r, a[100005], st[100005][30];
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
int main(){
    freopen("input.in", "r", stdin);
    n = read(), m = read();
    for(ri i = 0; i < n; i++) a[i] = read();
    for(ri i = 0; i < n; i++) st[i][0] = a[i];
    for(ri j = 1; (1 << j) <= n; j++)
        for(ri i = 0; i <= n - (1 << j); i++)
            st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
    while(m--){
        l = read(), r = read();
        l--, r--;
        int x = ceil(log2((r-l+2)/2));
        write(max(st[l][x], st[r-(1<<x)+1][x]));
        puts("");
    }
	return 0;
}