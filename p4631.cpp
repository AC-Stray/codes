#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define ri register int
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 300005;
int n, ans[N], id[N];
struct circle{
	int x, y, r, id;
	circle() {}
	circle(int x, int y, int r, int id): x(x), y(y), r(r), id(id) {}
	bool operator < (const circle &b) const { return r > b.r; }
}cc[N];
struct node{
	int val, bel;
	node() {}
	node(int val, int bel): val(val), bel(bel) {}
	bool operator < (const node &b) const { return val < b.val; }
	bool operator < (const int &b) const { return val < b; }
}pos[N<<1]; 
LL read(){
    ll n = 0; int f = 1; char ch = getchar();
    while('0' > ch || ch > '9'){
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while('0' <= ch && ch <= '9'){
        n = (n << 1) + (n << 3) + ch - '0';
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
int s(int x){
	return x * x;
}
bool check(int a, int b){
	return s(cc[a].x-cc[b].x) + s(cc[a].y-cc[b].y) <= s(cc[a].r + cc[b].r);
}
signed main(){
	input(n);
	for(ri i = 0; i < n; i++){
		input(cc[i].x, cc[i].y, cc[i].r);
		cc[i].id = i + 1;
		pos[i<<1] = node(cc[i].x - cc[i].r, i);
		pos[i<<1|1] = node(cc[i].x + cc[i].r, i);
	}
	sort(pos, pos + (n << 1));
	stable_sort(cc, cc + n);
	for(ri i = 0; i < n; i++) id[cc[i].id-1] = i;
	for(ri i = 0; i < n; i++){
		if(ans[cc[i].id-1]) continue;
		ans[cc[i].id-1] = cc[i].id;
		int start = lower_bound(pos, pos + (n << 1), cc[i].x - cc[i].r) - pos;
		for(ri j = start; j < (n << 1); j++){
			if(pos[j].val > cc[i].x + cc[i].r) break;
			if(ans[pos[j].bel]) continue;
			if(check(i, id[pos[j].bel])) ans[pos[j].bel] = cc[i].id;
		}
	}
	for(ri i = 0; i < n; i++) write(ans[i]), putchar(' ');
    return 0;
}
