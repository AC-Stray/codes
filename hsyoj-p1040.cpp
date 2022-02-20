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
const int N = 1000005;
int n, m1, m2, tnb2, tvb2;
ll ans, tota, totb;
struct magic{
	int val;
	ll num, tnum;
	magic() {}
	magic(int val, ll num): val(val), num(num), tnum(num) {}
	bool operator < (const magic &b) const { return val < b.val; }
}a[N], b1[N], b2[N];
#ifdef ONLINE_JUDGE
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++)
char buf[1000000], *p1(buf), *p2(buf);
#endif
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
ll solve2(){
	ll res = 0;
	for(ri i = 0, j = n - 1; i < m2 && j; i++){
		if(a[j].val < b2[i].val) break;
		if(a[j].tnum >= b2[i].tnum){
			a[j].tnum -= b2[i].tnum;
			res += 1ll * b2[i].tnum * (a[j].val - b2[i].val);
		}
		else{
			b2[i].tnum -= a[j].tnum;
			res += 1ll * a[j].tnum * (a[j].val - b2[i].val); 
			i--, j--;
		}
	}
	cerr << res << endl;
	return res;
}
ll solve1(){
	for(ri i = 0, j = 0; i < m1; i++){
		while(j < n - 1 && a[j].val < b1[i].val) j++;
		if(a[j].val < b1[i].val) return 0;
		if(a[j].tnum >= b1[i].tnum) a[j].tnum -= b1[i].tnum;
		else{
			b1[i].tnum -= a[j].tnum;
			a[j].tnum = 0;
			i--, j++;
		}
	}
	magic tmp(0, 2e18); m2++;
	for(ri i = 0; i < m2; i++) if(b2[i].val > 0 || i == m2 - 1) swap(tmp, b2[i]);
	return solve2();
}
int main(){
//	File(panwang15)
	n = read<int>(), m1 = read<int>(), m2 = read<int>();
	for(ri i = 0; i < n; i++){
		a[i].val = read<int>(), a[i].tnum = a[i].num = read<ll>();
		tota += a[i].num;
	}
	for(ri i = 0; i < m1; i++){
		b1[i].val = read<int>(), b1[i].tnum = b1[i].num = read<ll>();
		totb += b1[i].num;
	}
	for(ri i = 0; i < m2; i++) b2[i].val = read<int>(), b2[i].tnum = b2[i].num = read<ll>();
	sort(a, a + n); sort(b1, b1 + m1); sort(b2, b2 + m2);
	ans = solve2();
	if(tota >= totb){
		for(ri i = 0; i < n; i++) a[i].tnum = a[i].num;
		for(ri i = 0; i < m2; i++) b2[i].tnum = b2[i].num;
		ans = max(ans, solve1());
	}
	write(ans);
	return 0;
}
/*
Input
3 1 3
15 1
64 1
18 1
100 1
61 1
86 1
57 1
Output
7
*/
