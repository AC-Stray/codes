#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<vector>
#include<set>
#include<queue>
#include<string>
#include<cstring>
#include<map>
#include<list>
#include<deque>
#include<cctype>
#include<climits>
#include<cmath>
#include<ctime>
#include<algorithm>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
int n, m, cnt, mp[505][505], lt[505][505], rt[505][505];
int mv1[] = {1, -1, 0, 0}, mv2[] = {0, 0, 1, -1};
bool vis[505][505];
LL read(){
	ll n = 0; int f = 1; char ch = getchar();
	while('0' > ch || ch > '9'){
		if(ch == '-') f *= -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9'){
		n = (n << 1) + (n << 3) + ch-'0';
		ch = getchar();
	}
	return f * n;
}
Void write(ll x){
	if(x/10) write(x/10);
	putchar(x%10+'0');
}
Void input() {}
template<typename Type, typename... Types>
Void input(Type& arg, Types&... args){
    arg = read();
    input(args...);
}
Void dfs(int x, int y){
    vis[x][y] = true;
    for(ri i = 0; i < 4; i++){
        int nx = x + mv1[i], ny = y + mv2[i];
        if(mp[nx][ny] >= mp[x][y]) continue;
        if(!vis[nx][ny]) dfs(nx, ny);
        lt[x][y] = min(lt[x][y], lt[nx][ny]);
        rt[x][y] = max(rt[x][y], rt[nx][ny]);
    }
}
int main(){
    input(n, m);
    memset(mp, 0x3f, sizeof(mp));
    memset(lt, 0x3f, sizeof(lt));
    for(ri i = 1; i <= m; i++) lt[n][i] = rt[n][i] = i;
    for(ri i = 1; i <= n; i++) for(ri j = 1; j <= m; j++) input(mp[i][j]);
    for(ri i = 1; i <= m; i++) if(!vis[1][i]) dfs(1, i);
    cnt = 0;
    for(ri i = 1; i <= m; i++) if(!vis[n][i]) cnt++;
    if(cnt){
        puts("0");
        write(cnt);
        return 0;
    }
    for(ri i = 1; i <= m;){
        int maxr = 0;
        for(ri j = 1; j <= m; j++) if(lt[1][j] <= i) maxr = max(maxr, rt[1][j]);
        cnt++;
        i = maxr + 1;
    }
    puts("1");
    write(cnt);
	return 0;
}