#include<bits/stdc++.h>
using namespace std;
int n, ans, d[10005], p[10005], match[20005], edge[10005][2];
bool vis[20005];
inline bool dfs(int u){
	for(int i = 0; i < 2; i++){
		if(vis[edge[u][i]]) continue;
		vis[edge[u][i]] = true;
		if(match[edge[u][i]] == 0 || dfs(match[edge[u][i]])){
			match[edge[u][i]] = u;
			p[u] = edge[u][i];
			return true;
		}
	}
	return false;
}
int main(){
	cin >> n;
	for(int i = 0; i < n; i++) cin >> d[i];
	for(int i = 0; i < n; i++){
		edge[i][0] = (i + d[i]) % n;
		edge[i][1] = (i - d[i] + n) % n;
		if(edge[i][0] > edge[i][1]) swap(edge[i][0], edge[i][1]);
	}
	for(int i = n-1; i >= 0; i--){
		memset(vis, 0, sizeof(vis));
		if(dfs(i)) ans++;
	}
	if(ans < n) cout << "No Answer";
	else for(int i = 0; i < n; i++) cout << p[i] << " ";
	return 0;
}
