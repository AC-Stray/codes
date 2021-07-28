#include<bits/stdc++.h>
using namespace std;
int n, m, e, u, v, ans, match[505];
bool g[505][505], vis[505];
inline bool dfs(int u){
	for(int i = 1; i <= m; i++){
		if(!vis[i] && g[u][i]){
			vis[i] = true;
			if(match[i] == 0 || dfs(match[i])){
				match[i] = u;
				return true;
			}
		}
	}
	return false;
}
int main(){
	cin >> n >> m >> e;
	for(int i = 0; i < e; i++){
		cin >> u >> v;
		g[u][v] = true;
	}
	for(int i = 1; i <= n; i++){
		memset(vis, 0, sizeof(vis));
		if(dfs(i)) ans++;
	}
	cout << ans;
	return 0;
}
