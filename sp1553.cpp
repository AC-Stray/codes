#include<bits/stdc++.h>
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
struct node{
    int p;
    ll v;
    node() {}
    node(int p, ll v): p(p), v(v) {}
    Bool operator < (const node &b) const { return v > b.v; }
};
int t, l[100005], r[100005];
ll n, k, s, lst, ans, dst[100005];
bool vis[100005];
priority_queue<node>q;
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
int main(){
    input(t);
    while(t--){
        while(!q.empty()) q.pop();
        memset(vis, 0, sizeof(vis));
        ans = 0;
        input(n, k, lst);
        for(ri i = 1; i < n; i++) l[i] = i - 1, r[i] = i + 1;
        for(ri i = 1; i < n; i++){
            input(s);
            dst[i] = s - lst;
            q.push(node(i, s-lst));
            lst = s;
        }
        dst[0] = dst[n] = 0x3f3f3f3f;
        while(k--){
            while(vis[q.top().p]) q.pop();
            node now = q.top(); q.pop();
            vis[l[now.p]] = vis[r[now.p]] = true;
            // cout << now.v << endl;
            ans += now.v;
            dst[now.p] = dst[l[now.p]]+dst[r[now.p]]-dst[now.p];
            l[now.p] = l[l[now.p]];
            r[now.p] = r[r[now.p]];
            r[l[now.p]] = l[r[now.p]] = now.p;
            q.push(node(now.p, dst[now.p]));
        }
        write(ans); puts("");
    }
	return 0;
}