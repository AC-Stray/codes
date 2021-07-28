#include<bits/stdc++.h>
#define ri register int
#define int long long 
using namespace std;
int n, a, b, circle, ans;
struct line{
	int l, r;
	line() {}
	line(int l, int r): l(l), r(r) {}
	bool operator < (const line &b) const { return l == b.l ? r < b.r : l < b.l; }
};
vector<line> ls;
signed main(){
	cin >> n >> a >> b;
	circle = a * b / __gcd(a, b+1);
	for(ri i = 0, l, r; i < n; i++){
		cin >> l >> r;
		if(r - l + 1 >= circle) return cout << circle << endl, 0;
		l %= circle, r %= circle;
		if(l <= r) ls.emplace_back(l, r);
		else ls.emplace_back(0, r), ls.emplace_back(l, circle-1);
	}
	sort(ls.begin(), ls.end());
	line now = ls[0];
	for(ri i = 1; i < ls.size(); i++){
		if(ls[i].l <= now.r) now.r = max(now.r, ls[i].r);
		else{
			ans += now.r - now.l + 1;
			now = ls[i];
		}
	}
	ans += now.r - now.l + 1;
	cout << ans << endl;
	return 0;
}
