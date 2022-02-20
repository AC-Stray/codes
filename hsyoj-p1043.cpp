#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int D = 30005;
const int N = 1000005;
int n, d;
ll ans, tmp;
template<typename T, int SIZE>
struct exList{
	int Rpos;
	T a[SIZE], L, R;
	exList(int L = 0, int R = 0, int Rpos = SIZE): L(L), R(R), Rpos(Rpos) {}
	T& operator [] (const int &index){
		if(index < 0) return L;
		if(index >= Rpos) return R;
		return a[index];
	}
};
exList<ll, N> s, sum, val[2];
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++)
char buf[1000000], *p1(buf), *p2(buf);
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
int main(){
//	File(weather)
	n = read<int>(), d = read<int>();
	for(ri i = 0; i < n; i++) s[i] = read<ll>();
	for(ri i = 0; i < n; i++) sum[i] = sum[i-1] + s[i];
	sum.Rpos = n, sum.R = sum[n-1];
	val[0][0] = 0;
	for(ri i = 1; i < n; i++) val[0][i] = val[0][i-1]+s[i-d-1]-(2*d-1)*s[i-1]+2*(sum[i-2]-sum[i-d-1]);
	val[1][n-1] = 0;
	for(ri i = n - 2; i >= 0; i--) val[1][i] = val[1][i+1]-s[i+d+1]+(2*d-1)*s[i+1]-2*(sum[i+d]-sum[i+1]);
	for(ri i = 0; i < d; i++) ans += s[i] * (d - i) * (d - i);
	tmp = ans;
	for(ri i = 1; i < n; i++) tmp += val[0][i-1] + val[1][i-1], ans = max(ans, tmp);
	write(ans);
	return 0;
}
