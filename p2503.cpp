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
int n, m, a[25];
double avg, ans = 1e9;
priority_queue<int> q;
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
Void work(){
    random_shuffle(a, a+n);
    double sum = 0;
    for(ri i = 0; i < m; i++) q.push(0);
    for(ri i = 0; i < n; i++){
        int t = q.top();
        q.pop();
        t -= a[i];
        q.push(t);
    }
    while(!q.empty()){
        sum += (-1.0 * q.top() - avg) * (-1.0 * q.top() - avg);
        q.pop();
    }
    sum /= m * 1.0;
    sum = sqrt(sum);
    ans = min(ans, sum);
}
int main(){
    srand(19491001);
    n = rd, m = rd;
    for(ri i = 0; i < n; i++) a[i] = read(), avg += a[i];
    avg /= m * 1.0;
    while(clock()<=CLOCKS_PER_SEC*0.95) work();
    printf("%.2lf", ans);
	return 0;
}