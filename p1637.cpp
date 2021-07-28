#include<bits/stdc++.h>
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define ri register int
#define int long long
using namespace std;
typedef long long ll;
int n, m, ans, a[30005], t[30005], l[30005], r[30005], c[30005];
Int read(){
	int n = 0, f = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') f *= -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		n = (n << 1) + (n << 3) + ch-'0';
		ch = getchar();
	}
	return f * n;
}
Void write(int n){
	if(n / 10) write(n / 10);
	putchar(n%10+'0');
}
Int lowbit(int x){
	return x & -x;
}
Int query(int x){
	int sum = 0;
	for(ri i = x; i > 0; i -= lowbit(i)) sum += t[i];
	return sum;
}
Void add(int x, int y){
	for(ri i = x; i <= n; i += lowbit(i)) t[i] += y;
}
signed main(){
	n = read();
	for(ri i = 0; i < n; i++) c[i] = a[i] = read();
	sort(c, c+n);
	m = unique(c, c+n) - c;
	for(ri i = 0; i < n; i++) a[i] = lower_bound(c, c+m, a[i]) - c + 1;
	for(ri i = 0; i < n; i++){
		add(a[i], 1);
		l[i] = query(a[i]-1);
	}
	memset(t, 0, sizeof(t));
	for(ri i = n-1; i >= 0; i--){
		add(a[i], 1);
		r[i] = n - i - query(a[i]);
	}
	for(ri i = 0; i < n; i++) ans += l[i] * r[i];
	write(ans);
	return 0;
}
