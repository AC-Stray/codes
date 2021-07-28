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
int p, t, n, v[10005];
ll ans;
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
Void simulateAnneal(){
    for(register db temp = 5000; temp > 1e-10; temp *= 0.9112){
        int x = rand() % n + 1, y = rand() % n + 1;
        int sum1 = 0, sum2 = 0;
        swap(v[x], v[y]);
        for(ri i = 1; i <= (n+1)/2; i++) sum1 += v[i];
        for(ri i = (n+1)/2+1; i <= n; i++) sum2 += v[i];
        int sum = abs(sum1 - sum2); 
        if(sum < ans) ans = sum;
        else if(exp((ans-sum)/temp) < (double(rand())/RAND_MAX)) swap(v[x], v[y]);
    }
}
int main(){
    freopen("input.in", "r", stdin);
    srand(rand());
    cin >> t;
    while(t--){
        ans = 2147483647;
        cin >> n;
        for(ri i = 1; i <= n; i++) cin >> v[i];
        int tms = 1000;
        while(tms--) simulateAnneal();
        cout << ans << endl;
    }
	return 0;
}