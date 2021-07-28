#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<vector>
#include<set>
#include<queue>
#include<string>
#include<cstring>
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
ll n, k, l, r, ans, a[500005], sum[500005], st[500005][20];
Int rangeMax(int l, int r){
	int x = log2(r-l+1);
    return sum[st[l][x]] > sum[st[r-(1<<x)+1][x]] ? st[l][x] : st[r-(1<<x)+1][x];
}
struct node{
	int p, l, r, t;
	node(int p, int l, int r): p(p), l(l), r(r), t(rangeMax(l, r)) {}
	Bool operator < (const node &b) const{
		return sum[t] - sum[p-1] < sum[b.t] - sum[b.p-1];
	}
};
priority_queue<node> q;
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
	freopen("input.in", "r", stdin);
    input(n, k, l, r);
    for(ri i = 1; i <= n; i++) input(a[i]), sum[i] = sum[i-1] + a[i];
	for(ri i = 1; i <= n; i++) st[i][0] = i;
    for(ri j = 1; (1 << j) <= n; j++)
        for(ri i = 1; i <= n - (1 << j) + 1; i++)
            st[i][j] = sum[st[i][j-1]] > sum[st[i+(1<<(j-1))][j-1]] ? st[i][j-1] : st[i+(1<<(j-1))][j-1];
	for(ri i = 1; i + l - 1 <= n; i++)
		q.push(node(i, i+l-1, min(i+r-1, n)));
	while(k--){
		node now = q.top();
		q.pop();
		ans += sum[now.t] - sum[now.p-1];
		if(now.t != now.l) q.push(node(now.p, now.l, now.t-1));
		if(now.t != now.r) q.push(node(now.p, now.t+1, now.r));
	}
	cout << ans;
	return 0;
}