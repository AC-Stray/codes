#include<bits/stdc++.h>
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 100005;
int b;
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
namespace solve1{
	int n, d, m, a[N];
	ll ans = 0;
	void main(){
		input(n, d, m);
		for(ri i = 0; i < n; i++) input(a[i]);
		sort(a, a + n);
		for(ri i = 0, j = 0; i < n; i++){
			while(a[i] - a[j] > d && j < i) j++;
			ans += i - j;
		}
		write(ans);
	}
}
namespace solve2{
	const int M = 75000;
	int n, d, m, tree[M<<2];
	ll ans;
	struct node{
		int x, y;
		bool operator < (const node &b) const { return x < b.x; }
	}a[N];
	int lowbit(int x){
		return x & -x;
	}
	void add(int x, int y){
		for(ri i = x; i <= 4 * m; i += lowbit(i)) tree[i] += y;
	}
	ll query(int x){
		ll res = 0;
		for(ri i = x; i > 0; i -= lowbit(i)) res += tree[i];
		return res;
	}
	void main(){
		input(n, d, m);
		for(ri i = 0, x, y; i < n; i++){
			input(x, y);
			a[i] = {x + y, x - y + 2 * m};
		}
		sort(a, a + n);
		add(a[0].y, 1);
		for(ri i = 1, j = 0; i < n; i++){
			while(a[i].x - a[j].x > d && j < i) add(a[j++].y, -1);
			ans += query(a[i].y + d) - query(a[i].y - d - 1);
			add(a[i].y, 1);
		}
		write(ans);
	}
}
namespace solve3{
	const int M = 75 + 5;
	int n, d, m, cnt[M][M<<1][M<<1];
	int s[M][M<<1][M<<1];
	ll ans;
	struct node{
		int x, y, z;
	}a[N];
	int sum(int z, int x1, int y1, int x2, int y2){
		return s[z][x2][y2] - s[z][x2][y1-1] - s[z][x1-1][y2] + s[z][x1-1][y1-1];
	}
	void main(){
		input(n, d, m);
		for(ri i = 0, x, y, z; i < n; i++){
			input(x, y, z);
			a[i] = {x + y, x - y + m, z} ;
		}
		for(ri i = 0; i < n; i++) cnt[a[i].z][a[i].x][a[i].y]++;
		for(ri i = 1; i <= m; i++){
			for(ri j = 1; j <= (m<<1); j++){
				for(ri k = 1; k <= (m<<1); k++){
					s[i][j][k] += s[i][j-1][k] + s[i][j][k-1] - s[i][j-1][k-1] + cnt[i][j][k];
				}
			}
		}
		for(ri i = 0; i < n; i++){
			for(ri j = max(1, a[i].z-d); j <= min(m, a[i].z+d); j++){
				int dis = d - abs(a[i].z - j);
				int x1 = max(1, a[i].x - dis);
				int x2 = min(m<<1, a[i].x + dis);
				int y1 = max(1, a[i].y - dis);
				int y2 = min(m<<1, a[i].y + dis);
				ans += sum(j, x1, y1, x2, y2);
			}
		} 
		ans = (ans - n) >> 1;
		write(ans);
	}
}
int main(){
	input(b);
	switch(b){
		case 1: solve1::main(); break;
		case 2: solve2::main(); break;
		case 3: solve3::main(); break;
	}
	return 0;
}
