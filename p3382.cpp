#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdio>
#include<vector>
#include<set>
#include<queue>
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
#define LL inline long long
#define ri register int
#define gc getchar()
#define rd read()
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
int n;
db l, r, ans, x[15];
LL read(){
	ll n = 0; int f = 1; char ch = gc;
	while('0' > ch || ch > '9'){
		if(ch == '-') f *= -1;
		ch = gc;
	}
	while('0' <= ch && ch <= '9'){
		n = (n << 1) + (n << 3) + ch-'0';
		ch = gc;
	}
	return f * n;
}
Void write(ll x){
	if(x/10) write(x/10);
	putchar(x%10+'0');
}
inline db cal(db nn){
    db res = 0;
    for(ri i = 0; i <= n; i++)
        res += x[i] * pow(nn, n-i);
    return res;
}
Void pa(){
    db now = l, step = r - l;
    while(step > 1e-7){
        if(now - step >= l && cal(now - step) > cal(now)) now -= step;
        else if(now + step <= r && cal(now + step) > cal(now)) now += step;
        step *= 0.998;
    }
    ans = now;
}
int main(){
    cin >> n >> l >> r;
    for(ri i = 0; i <= n; i++) cin >> x[i];
    pa();
    printf("%.5lf", ans);
	return 0;
}