#include<bits/stdc++.h>
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 100005;
int n, nums[N<<1];
struct scanline{
	int x, y1, y2, mark;
	bool operator < (const scanline &b) const { return x < b.x; }
}line[N<<1];
struct segtree{
	int l, r, sum, len;
}tree[N<<4];
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
void input(Type& arg, Types&... args){
	arg = read<Type>();
	input(args...);
}
void pushup(int p){
	int l = tree[p].l, r = tree[p].r;
	if(tree[p].sum) tree[p].len = nums[r+1] - nums[l];
	else tree[p].len = tree[p<<1].len + tree[p<<1|1].len;
}
void build(int p, int l, int r){
	tree[p].l = l, tree[p].r = r;
	tree[p].sum = tree[p].len = 0;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(p<<1, l, mid);
	build(p<<1|1, mid+1, r);
}
void modify(int p, int L, int R, int c){
	int l = tree[p].l, r = tree[p].r;
	if(nums[r+1] <= L || nums[l] >= R) return;
	if(nums[l] >= L && nums[r+1] <= R) tree[p].sum += c;
	else modify(p<<1, L, R, c), modify(p<<1|1, L, R, c);
	pushup(p);
}
signed main(){
	input(n);
	for(ri i = 0, _x, _y, __x, __y; i < n; i++){
		input(_x, _y, __x, __y);
		line[i<<1] = {_x, _y, __y, 1};
		line[i<<1|1] = {__x, _y, __y, -1};
		nums[i<<1] = _y;
		nums[i<<1|1] = __y;
	}
	sort(line, line + (n<<1));
	sort(nums, nums + (n<<1));
	int k = unique(nums, nums + (n<<1)) - nums;
	build(1, 0, k - 2);
	ll ans = 0;
	for(ri i = 0; i < (n<<1)-1; i++){
		modify(1, line[i].y1, line[i].y2, line[i].mark);
		ans += tree[1].len * (line[i+1].x - line[i].x);
	}
	write(ans);
	return 0;
}
