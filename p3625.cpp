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
int m, n, k, ans;
int t, s[1505][1505], ul[1505][1505], ur[1505][1505], dl[1505][1505], dr[1505][1505];
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
    // freopen("large-1.in", "r", stdin);
    input(m, n, k);
    for(ri i = 1; i <= m; i++) for(ri j = 1; j <= n; j++) input(t),s[i][j]=s[i][j-1]+s[i-1][j]-s[i-1][j-1]+t;
    for(ri i = m; i >= k; i--) for(ri j = n; j >= k; j--) s[i][j]=s[i][j]-s[i][j-k]-s[i-k][j]+s[i-k][j-k];
    for(ri i = k; i <= m; i++) for(ri j = k; j <= n; j++) ul[i][j]=max(s[i][j],max(ul[i-1][j],ul[i][j-1]));
    for(ri i = m; i >= k; i--) for(ri j = k; j <= n; j++) dl[i][j]=max(s[i][j],max(dl[i+1][j],dl[i][j-1]));
    for(ri i = k; i <= m; i++) for(ri j = n; j >= k; j--) ur[i][j]=max(s[i][j],max(ur[i-1][j],ur[i][j+1]));
    for(ri i = m; i >= k; i--) for(ri j = n; j >= k; j--) dr[i][j]=max(s[i][j],max(dr[i+1][j],dr[i][j+1]));
    for(ri i = k; i <= m-k; i++) for(ri j = k; j <= n-k; j++) ans=max(ans,ul[i][j]+dl[i+k][n]+ur[i][j+k]);
    // cout << ans << endl;
    for(ri i = k; i <= m-k; i++) for(ri j = k; j <= n-k; j++) ans=max(ans,ul[i][n]+dl[i+k][j]+dr[i+k][j+k]);
    // cout << ans << endl;
    for(ri i = k; i <= m-k; i++) for(ri j = k; j <= n-k; j++) ans=max(ans,ul[i][j]+dl[i+k][j]+ur[m][j+k]);
    // cout << ans << endl;
    for(ri i = k; i <= m-k; i++) for(ri j = k; j <= n-k; j++) ans=max(ans,ul[m][j]+ur[i][j+k]+dr[i+k][j+k]);
    // cout << ans << endl;
    for(ri i = 2*k; i <= m-k; i++) for(ri j = k; j <= n-k; j++) ans=max(ans,ul[i-k][n]+dl[i+k][n]+s[i][j]);
    // cout << ans << endl;
    for(ri i = k; i <= m-k; i++) for(ri j = 2*k; j <= n-k; j++) ans=max(ans,ul[m][j-k]+ur[m][j+k]+s[i][j]);
    // cout << ans << endl;
    write(ans);
    return 0;
}