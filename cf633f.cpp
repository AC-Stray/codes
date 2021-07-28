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
ll n, u, v, a[100005], dp[100005][5];
vector<int> g[100005];
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
Void dfs(int now, int fa){
    // 初始化
    dp[now][0] = dp[now][1] = dp[now][2] = dp[now][4] = a[now];
    dp[now][3] = 0;

    for(auto x: g[now]){
        if(x == fa) continue;
        dfs(x, now);

        /* ***************************************** *
        * dp[][0]: 最大两条链之和
        * dp[][1]: 最大一条链
        * dp[][2]: 到叶子节点的链+一条与之不相交的链最大值
        * dp[][3]: 儿子节点dp[][1]最大值
        * dp[][4]: 到叶子节点的最大链
        * ***************************************** */

        dp[now][0] = max(dp[now][0], dp[now][1] + dp[x][1]);           // 子树内最大一条链+子节点子树内最大一条链
        dp[now][0] = max(dp[now][0], dp[x][0]);                        // 从子节点直接转移
        dp[now][0] = max(dp[now][0], dp[x][2] + dp[now][4]);           // 子节点子树内到叶子节点的链 与 子树内到叶子节点的链构成一条穿过当前节点的链+一条与之不相交的链
        dp[now][0] = max(dp[now][0], dp[now][2] + dp[x][4]);           // 与上面的转移类似

        dp[now][1] = max(dp[now][1], dp[x][1]);                        // 从子节点直接转移
        dp[now][1] = max(dp[now][1], dp[now][4] + dp[x][4]);           // 子节点子树内到叶子节点的链 与 子树内到叶子节点的链构成一条穿过当前节点的链

        dp[now][2] = max(dp[now][2], dp[x][2] + a[now]);               // 从子节点直接转移，将子节点子树内那条到达叶子结点的链延伸到当前节点
        dp[now][2] = max(dp[now][2], dp[x][4] + dp[now][3] + a[now]);  // 与上面的转移类似
        dp[now][2] = max(dp[now][2], dp[now][4] + dp[x][1]);           // 按照dp[][2]的定义直接转移

        dp[now][3] = max(dp[now][3], dp[x][1]);                        // 按照dp[][3]的定义直接转移

        dp[now][4] = max(dp[now][4], dp[x][4] + a[now]);               // 按照dp[][4]的定义直接转移，将最大链延伸到当前节点
    }
}
int main(){
    input(n);
    for(ri i = 1; i <= n; i++) input(a[i]);
    for(ri i = 1; i < n; i++){
        input(u, v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    write(dp[1][0]);
	return 0;
}