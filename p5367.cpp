#include<bits/stdc++.h>
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define ri register int
using namespace std;
typedef long long ll;
const int MOD = 998244353;
int ans, n, a[1000005], t[1000005], f;
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
Void add(int x, int y){
	for(ri i = x; i <= n; i += lowbit(i)) t[i] = (t[i] + y) % MOD;
}
Int query(int x){
	int sum = 0;
	for(ri i = x; i > 0; i -= lowbit(i)) sum = (sum + t[i]) % MOD;
	return sum;
}
int main(){
	n = read();
	for(ri i = 0; i < n; i++) a[i] = read();
	f = 1;
	for(ri i = n-1; i >= 0; i--){
		ans = (ans + query(a[i]-1) % MOD * f % MOD) % MOD;
		add(a[i], 1);
		f = f * (n - i) % MOD;
	}
	write((ans + 1) % MOD);
	return 0;
}

