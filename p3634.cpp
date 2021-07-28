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
int n, k, m, now, cnt, b[100005];
int L[100005], R[100005], v[100005];
int top;
int f[100005], g[100005], l, r;
struct line{
    int l, r, f;
    Bool operator < (const line &b) const { return l < b.l; }
}a[100005];
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
    input(n, k, m);
    for(ri i = 1; i <= m; i++){
        input(a[i].l, a[i].r, a[i].f);
        if(a[i].f == 0){
            b[a[i].l]  ++;
            b[a[i].r+1]--;
        }
    }
    for(ri i = 1; i <= n; i++){
        now += b[i];
        if(now == 0){
            L[i] = R[i] = ++cnt;
            v[cnt] = i;
        }
    }
    if(cnt == k){
        for(ri i = 1; i <= cnt; i++) cout << v[i] << endl;
        return 0;
    }
    L[n+1] = n + 1;
    for(ri i = n; i >= 1; i--) if(L[i] == 0) L[i] = L[i+1];
    for(ri i = 1; i <= n; i++) if(R[i] == 0) R[i] = R[i-1];
    cnt = 0;
    for(ri i = 1; i <= m; i++){
        if(a[i].f == 0) continue;
        a[i].l = L[a[i].l], a[i].r = R[a[i].r];
        if(a[i].l <= a[i].r) a[cnt++] = (line){a[i].l, a[i].r, 1};
    }
    stable_sort(a, a + cnt);
    for(ri i = 0; i < cnt; i++){
        while(top != 0 && a[i].l >= L[top] && a[i].r <= R[top]) top--;
        L[++top] = a[i].l;
        R[top]   = a[i].r;
    }
    l = n + 1, r = 0;
    for(ri i = 1; i <= top; i++){
        if(L[i] > r) f[i] = f[i-1] + 1, r = R[i];
        else         f[i] = f[i-1];
    }
    for(ri i = top; i >= 1; i--){
        if(R[i] < l) g[i] = g[i+1] + 1, l = L[i];
        else         g[i] = g[i+1];
    }
    bool flag = false;
    for(ri i = 1; i <= top; i++){
        if(f[i] == f[i-1]) continue;
        if(L[i] == R[i]){
            flag = true;
            cout << v[R[i]] << endl;
            continue;
        }
        int x = 0, y = top + 1, lll = 1, rrr = i - 1;
        while(lll <= rrr){
            int mid = lll + ((rrr-lll) >> 1);
            if(R[mid] < R[i] - 1) x = mid, lll = mid + 1;
            else rrr = mid - 1;
        }
        lll = i + 1, rrr = top;
        while(lll <= rrr){
            int mid = lll + ((rrr-lll) >> 1);
            if(L[mid] > R[i] - 1) y = mid, rrr = mid - 1;
            else lll = mid + 1;
        }
        // int x = lower_bound(R+1, R+i, R[i]-1) - R - 2;
        // int y = upper_bound(L+i+1, L+top+1, R[i]-1) - L;
        if(f[x] + g[y] + 1 > k){
            flag = true;
            cout << v[R[i]] << endl;
        }
    }
    if(!flag) puts("-1");
    return 0;
}