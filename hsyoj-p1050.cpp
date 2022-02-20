#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define int long long 
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 100005;
const int M = 105;
int n, m, k, ca, ts, a[N], col[M], row[N], cnt[N*M], val[M*M];
ll ans;
bool mp[N][M];
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
bool readmp(){
	char ch = getchar();
	while(ch != '.' && ch != '$') ch = getchar();
	return ch == '$';
}
signed main(){
//	File(treasure)
	n = read<int>(), m = read<int>(), k = read<int>();
	for(ri i = 1; i <= n; i++){
		for(ri j = 1; j <= m; j++){
			mp[i][j] = readmp();
			row[i] += mp[i][j];
			col[j] += mp[i][j];
		}
	}
	for(ri i = 1; i <= m; i++){
		int sum = 0;
		for(ri j = i; j <= m; j++){
			sum += col[j];
			a[ca++] = sum;
		}
	}
	sort(a, a + ca);
	for(ri i = 0, j = 0; i < ca; i++){
		if(i != 0 && a[i] != a[i-1]) j++;
		val[j]++;
	}
	ca = unique(a, a + ca) - a;
	for(ri i = 1; i <= n; i++) row[i] += row[i-1];
	cnt[0] = 1;
	cerr << (double)clock()/CLOCKS_PER_SEC << ' ' << ca << endl;
	for(ri i = 1; i <= n; i++){
		for(ri j = 0; j < ca; j++){
			if(k - a[j] < 0) break;
			if(row[i] - k + a[j] >= 0 && cnt[row[i]-k+a[j]]) ans += cnt[row[i]-k+a[j]] * val[j];
		}
		cnt[row[i]]++;
	}
	write(ans);
	return 0;
}
