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
namespace Main{
	const int inf = 2e18;
	const int N = 1000005;
	int n, x, pos[N], neg[N], sum[N], c1, c2;
	Int dsum(int l, int r) { return (l + r) * (r - l + 1) / 2; }
	int calc(int a, int b){
		if(a + b == 18){
			cerr << "";
		}
		if(a > c2 || b > c1) return inf;
		int res = 0;
		res += dsum(0, a - 1) - neg[a-1];
		int l = 0, r = b - 1, p = b - 1;
		while(l <= r){
			int mid = l + r >> 1;
			if(pos[mid] >= a + mid) r = mid - 1, p = mid;
			else l = mid + 1;
		}
		if(p) res += dsum(a, a + p - 1) - sum[p-1];
		res += sum[b-1] - (p ? sum[p-1] : 0) - dsum(a + p, a + b - 1);
		return res;
	}
	bool check(int mid){
		for(ri i = max(0ll, mid - c1); i <= min(mid, c2); i++) if(calc(i, mid - i) <= x) return true;
		return false;
	}
	void Main(){
		n = read<int>(), x = read<int>();
		for(ri i = 0, tmp; i < n; i++){
			tmp = read<int>();
			if(tmp >= 0) pos[c1++] = tmp;
			else neg[c2++] = tmp;
		}
		sort(pos, pos + c1);
		sort(neg, neg + c2, greater<int>());
		sum[0] = pos[0];
		for(ri i = 1; i < c1; i++) sum[i] = sum[i-1] + pos[i];
		for(ri i = 1; i < c2; i++) neg[i] += neg[i-1];
		int l = 0, r = n, ans = 0;
		while(l <= r){
			int mid = l + r >> 1;
			if(check(mid)) l = mid + 1, ans = mid;
			else r = mid - 1;
		}
		write(ans);
		return;
	}
}
signed main(){
//	File(dream)
	Main::Main();
	return 0;
}

