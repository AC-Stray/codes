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
int n, ans, px[N], py[N], f[N], g[N];
struct node{
	int v, id;
	bool operator < (const node &b) const { return v < b.v; }
}x[N], y[N];
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
signed main(){
	input(n);
	for(ri i = 0, x0, y0; i < n; i++){
		input(x0, y0);
		x[i] = {x0 + y0, i};
		y[i] = {x0 - y0, i};
	}
	sort(x, x + n);
	sort(y, y + n);
	for(ri i = 0; i < n; i++){
		px[x[i].id] = i;
		py[y[i].id] = i;
	}
	for(ri i = 1; i < n; i++){
		f[0] += x[i].v - x[0].v;
		g[0] += y[i].v - y[0].v;
	}
	for(ri i = 1; i < n; i++){
		f[i] = f[i-1] + (2 * i - n) * (x[i].v - x[i-1].v);
		g[i] = g[i-1] + (2 * i - n) * (y[i].v - y[i-1].v);
	}
	ans = 1e18;
	for(ri i = 0; i < n; i++) ans = min(ans, f[px[i]] + g[py[i]]);
	write(ans>>1);
	return 0;
}
