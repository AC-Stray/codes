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
int k, n, num[25], sum, cnt, pp, tmp, ans;
int p[1005];
bool vis[1005];
vector<int> g[25];
vector<int> G[1005];
priority_queue<int, vector<int>, greater<int>> q;
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
bool match(int x){
    for(ri i = 0; i < G[x].size(); i++){
        int v = G[x][i];
        if(!vis[v]){
            vis[v] = true;
            if(!p[v] || match(p[v])){
                p[v] = x;
                return true;
            }
        }
    }
    return false;
}
int main(){
    input(k, n);
    for(ri i = 1; i <= k; i++){
        input(num[i]);
        sum += num[i];
        for(ri j = 0; j < num[i]; j++) g[i].push_back(cnt++);
    }
    for(ri i = 1; i <= n; i++){
        input(pp);
        for(ri j = 0; j < pp; j++){
            input(tmp);
            for(ri k = 0; k < g[tmp].size(); k++){
                int v = g[tmp][k];
                G[i].push_back(v);
            }
        }
    }
    for(ri i = 1; i <= n; i++){
        memset(vis, 0, sizeof(vis));
        if(match(i)) ans++;
    }
    if(ans < sum) puts("No Solution!");
    else{
        for(ri i = 1; i <= k; i++){
            for(ri j = 0; j < g[i].size(); j++) q.push(p[g[i][j]]);
            cout << i << ':';
            while(!q.empty()) cout << ' ' << q.top(), q.pop();
            cout << endl;
        }
    }
    return 0;
}