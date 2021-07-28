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
struct line{
    int l, r, id;
}lines[2000005];
struct node{
    int pos, belong;
    node() {}
    node(int pos, int belong): pos(pos), belong(belong) {}
    Bool operator < (const node &b) const{
        return pos < b.pos;
    }
};
set<node> s;
int n, HASH[2000005], top, lft[2000005][25], ans, pre[2000005], __id[2000005];
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
Bool cmp1(line l1, line l2){
    if(l1.l != l2.l) return l1.l < l2.l;
    else return l1.r < l2.r;
}
Bool cmp2(line l1, line l2){
    return l1.id < l2.id;
}
Int count(int l, int r){
    int res = 0, p = r;
    for(ri i = 20; i >= 0; i--)
        if(lft[p][i] && lines[lft[p][i]].l > l) res += (1 << i), p = lft[p][i];
    return res;
}
int main(){
    freopen("input.in", "r", stdin);
    input(n);
    for(ri i = 1; i <= n; i++)
        input(lines[i].l, lines[i].r), lines[i].id = i, HASH[++top] = lines[i].l, HASH[++top] = lines[i].r;
    sort(HASH+1, HASH+top+1);
    top = unique(HASH+1, HASH+top+1) - HASH - 1;
    sort(lines+1, lines+n+1, cmp1);
    for(ri i = 1; i <= n; i++){
        lines[i].l = lower_bound(HASH+1, HASH+top+1, lines[i].l) - HASH;
        lines[i].r = lower_bound(HASH+1, HASH+top+1, lines[i].r) - HASH;
    }
    for(int i = 1; i <= n; i++){
        if(pre[lines[i].r] < lines[i].l){
            pre[lines[i].r] = lines[i].l;
            __id[lines[i].r] = lines[i].id;
        }
    }
    for(int i = 1; i <= top; i++){
        if(pre[i] < pre[i-1])
            pre[i] = pre[i-1], __id[i] = __id[i-1];
    }
    for(ri i = 1; i <= n; i++){
        lft[lines[i].id][0] = __id[lines[i].l-1];
        for(ri j = 1; j <= 20; j++)
            lft[lines[i].id][j] = lft[lft[lines[i].id][j-1]][j-1];
    }
    int tPos = 0;
    for(ri i = 1; i <= n; i++)
        if(tPos == 0 || lines[tPos].l < lines[i].l) tPos = i;
    tPos = lines[tPos].id;
    lft[n+1][0] = tPos;
    for(ri i = 1; i <= 20; i++)
        lft[n+1][i] = lft[lft[n+1][i-1]][i-1];
    for(ri i = 20; i >= 0; i--)
        if(lft[tPos][i]) ans += (1 << i), tPos = lft[tPos][i];
    write(ans+1), puts("");
    sort(lines+1, lines+n+1, cmp2);
    s.insert(node(0, 0));
    s.insert(node(1e9, n+1));
    for(ri i = 1; i <= n; i++){
        if(s.lower_bound(node(lines[i].l, 0)) != s.lower_bound(node(lines[i].r, 0))) continue;
        set<node>::iterator iter = s.lower_bound(node(lines[i].l, 0));
        node suc = *iter, pre = *(--iter);
        if(count(pre.pos, i) + count(lines[i].r, suc.belong) + 1 != count(pre.pos, suc.belong)) continue;
        write(i), putchar(' ');
        s.insert(node(lines[i].l, i));
        s.insert(node(lines[i].r, i));
    }
	return 0;
}