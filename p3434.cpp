#include<bits/stdc++.h>
using namespace std;
int n, m, ans, r[300005], k;
int main(){
	cin >> n >> m;
	ans = n;
	for(int i = 0; i < n; i++){
		cin >> r[i];
		if(!i == 0 && r[i] > r[i-1]) r[i] = r[i-1];
	}
	for(int i = 0; i < m; i++){
		cin >> k;
		ans = upper_bound(r, r+ans-1, k, greater<int>())-r;
	}
	cout << ans;
	return 0;
} 
