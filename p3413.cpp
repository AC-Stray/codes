#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
#define int ll
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
const int MOD = 1e9+7;
string l, r;
int res, numl, numr;
int split[1005], f[1005][10][10];
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
Int dfs(int p, int lst, int llst, bool op, bool start){
    if(p == 0) return 1;
    if(!op && lst != -1 && llst != -1 && f[p][lst][llst] != -1) return f[p][lst][llst];
    int mx = op ? split[p] : 9, rt = 0;
    for(ri i = 0; i <= mx; i++){
        if(i == lst || i == llst) continue;
        if(i == 0 && start) rt = (rt + dfs(p-1, -1, -1, op & (i==mx), true)) % MOD;
        else rt = (rt + dfs(p-1, i, lst, op & (i==split[p]), false)) % MOD;
    } 
    if(!op && lst != -1 && llst != -1) f[p][lst][llst] = rt;
    return rt;
}
Int ans(string n){
    memset(f, -1, sizeof(f));
    for(ri i = 0; i < n.size(); i++) split[n.size()-i] = n[i] - '0';
    return dfs(n.size(), -1, -1, true, true);
}
signed main(){
    cin >> l >> r;
    for(ri i = 0; i < l.size(); i++) numl = (numl * 10 + l[i]-'0') % MOD;
    for(ri i = 0; i < r.size(); i++) numr = (numr * 10 + r[i]-'0') % MOD;
    // cout << numr << ' ' << numl << endl;
    res = (numr-numl+1 - (ans(r)-ans(l)) + MOD) % MOD;
    bool flag = false;
    for(ri i = 2; i < l.size(); i++){
        if(l[i] == l[i-1] || l[i] == l[i-2]){
            flag = true;
            break;
        }
    }
    // cout << flag << endl;
    if(!flag) res = (res - 1 + MOD) % MOD;
    write(res);
	return 0;
}