#include<bits/stdc++.h>
using namespace std;
int n, m[35][35], ans, t;
int main(){
	while(true){
		cin >> n;
		if(n == 0) break;
		memset(m, 0, sizeof(m));
		for(int i = 0; i < n-1; i++) for(int j = i+1; j < n; j++)
			cin >> m[i][j], m[j][i] = m[i][j];
		ans = m[0][1];
		for(int i = 2; i < n; i++){
			t = 0x7fffffff;
			for(int j = 0; j < i; j++)
				for(int k = j+1; k < i; k++)
					t = min(t, (m[j][i]+m[k][i]-m[j][k]) / 2);
			ans += t;
		}
		cout << ans << endl;
	}
	return 0;
} 
