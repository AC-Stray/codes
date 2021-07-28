#include<bits/stdc++.h>
//#define DEBUG
using namespace std;
struct sqr{
	int x, y, v;
}h[1000005];
int m, n, ans, mp[1005][1005], fa[1000005], ma[1000005];
int mv1[] = {1, -1, 0, 0}, mv2[] = {0, 0, 1, -1};
bool cmp(sqr a, sqr b){
	return a.v < b.v;
}
int get(int a){
	if(fa[a] == a) return a;
	return fa[a] = get(fa[a]);
}
void unite(int a, int b){
	int A = get(a), B = get(b);
	fa[A] = B;
	ma[B] |= ma[A];
}
int pos(int a, int b){
	return a * n + b;
}
int main(){
	freopen("input.txt", "r", stdin);
	cin >> m >> n;
	for(int i = 0; i < m; i++) for(int j = 0; j < n; j++){
		cin >> mp[i][j];
		h[pos(i, j)].x = i, h[pos(i, j)].y = j, h[pos(i, j)].v = abs(mp[i][j]);
	}
	sort(h, h+n*m, cmp);
	for(int i = 0; i < n * m; i++) fa[i] = i;
	for(int j = 0; j < n * m; j++){
		for(int k = 0; k < 4; k++){
			int nx = h[j].x + mv1[k], ny = h[j].y + mv2[k];
			if(nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
			if(h[j].v >= abs(mp[nx][ny])) unite(pos(nx, ny), pos(h[j].x, h[j].y));
		}
		if(h[j].v != h[j+1].v){
			for(int i = j; h[i].v == h[j].v; i--){
				if(mp[h[i].x][h[i].y] > 0 && ma[get(pos(h[i].x, h[i].y))] == 0){
					ma[get(pos(h[i].x, h[i].y))] = 1;
					ans++;	
				}	
			}
		}
	}
	#ifdef DEBUG
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++)
				cout << setw(3) << fa[pos(i, j)];
			cout << endl;
		}
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++)
				cout << setw(3) << ma[pos(i, j)];
			cout << endl;
		}
	#endif
	cout << ans;
	return 0;
}
