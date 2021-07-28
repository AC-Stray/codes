#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define DB inline double
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
struct node{
	int v, id;
	Bool operator < (const node &b) const{
		return v < b.v;
	}
};
int n, p, u, v, maxp, maxv, ans, globalAns,child[305], father[305];
vector<int> g[305];
vector<node> depth;
LL read(){
	ll n = 0; int f = 1; char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') f *= -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		n = n * 10 + ch-'0';
		ch = getchar();
	}
	return f * n;
}
Void write(ll n){
	if(n / 10) write(n / 10);
	putchar(n%10+'0');
}
Void input() {}
template<typename Type, typename... Types>
Void input(Type& arg, Types&... args){
	arg = read();
	input(args...);
}
Void Init(int now, int fa){
	father[now] = fa;
	child[now] = 0;
	for(auto x: g[now]) if(x != fa){
		Init(x, now);
		child[now] += child[x]+1;
	}
}
Void depthInit(int now, int fa){
	depth[now].v = depth[fa].v + 1;
	depth[now].id = now;
	for(auto x: g[now])
		if(x != fa) depthInit(x, now);
}
Void del(int id, int fa){
	for(ri i = 0; i < depth.size(); i++)
		if(depth[i].id == id) depth.erase(depth.begin()+i);
	for(auto x: g[id]) if(x != fa) del(x, id);
}
Void work(int now){
    if(now > depth[depth.size()-1].v){
        globalAns = min(globalAns, ans);
        return;
    }
    vector<node> save;
    for(auto x: depth) save.push_back(x);
	for(ri j = lower_bound(depth.begin(), depth.end(), (node){now, 0})-depth.begin(); j < upper_bound(depth.begin(), depth.end(), (node){now, 0})-depth.begin(); j++){
	    ans -= child[depth[j].id] + 1;
        del(depth[j].id, father[depth[j].id]);
        work(now+1);
        depth.clear();
        for(auto x: save) depth.push_back(x);
        ans += child[depth[j].id] + 1;
    }
}
int main(){
	input(n, p);
	for(ri i = 0; i < p; i++){
		input(u, v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
    Init(1, 0);
	depth.resize(n+1);
	depthInit(1, 0);
	sort(depth.begin(), depth.end());
	ans = n;
    if(n <= 100){
        globalAns = 0x7fffffff;
	    work(2);
        write(globalAns); 
    }
    else{
        ans = n;
        for(ri i = 2; i <= depth[depth.size()-1].v; i++){
            maxv = -1;
            for(ri j = lower_bound(depth.begin(), depth.end(), (node){i, 0})-depth.begin(); j < upper_bound(depth.begin(), depth.end(), (node){i, 0})-depth.begin(); j++){
                if(child[depth[j].id] > maxv)
                    maxv = child[depth[j].id], maxp = depth[j].id;
            }
            del(maxp, father[maxp]);
            ans -= maxv + 1;
        }
        write(ans);
    }
	return 0;
}