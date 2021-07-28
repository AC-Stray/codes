#include<bits/stdc++.h>
using namespace std;
struct square{
	int x1, y1, x2, y2, c;
}sqrs[20];
int n, ans;
bool vis[20];
bool cmp(square s1, square s2){
	if(s1.y1 != s2.y1) return s1.y1 < s2.y1;
	return s1.x1 < s2.x1;
}
bool check(int x){
	for(int i = 0; i < x; i++)
		if(!vis[i] && sqrs[i].y2 == sqrs[x].y1 && (
		  (sqrs[i].x1 >= sqrs[x].x1 && sqrs[i].x1 <= sqrs[x].x2) || 
		  (sqrs[i].x2 >= sqrs[x].x1 && sqrs[i].x2 <= sqrs[x].x2)
		)) return false;
	return true;
}
void dfs(int p, int c, int a){
	if(p == n) ans = min(ans, a);
	if(a >= ans) return;
	for(int i = 0; i < n; i++){
		if(vis[i]) continue;
		if(!check(i)) continue;
		vis[i] = true;
		if(sqrs[i].c == c) dfs(p+1, c, a);
		else dfs(p+1, sqrs[i].c, a+1);
		vis[i] = false;
	}
}
int main(){
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> sqrs[i].y1 >> sqrs[i].x1 >> sqrs[i].y2 >> sqrs[i].x2 >> sqrs[i].c;
	sort(sqrs, sqrs+n, cmp); 
	ans = 0x7fffffff;
	dfs(0, -1, 0);
	cout << ans;
	return 0;
}
