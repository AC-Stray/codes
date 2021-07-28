#include<bits/stdc++.h>
using namespace std;
int n, t;
vector<int>q;
int main(){
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> t;
		q.insert(upper_bound(q.begin(), q.end(), t), t);
		if(i % 2 == 0) cout << q[i/2] << endl;
	}
	return 0;
}
