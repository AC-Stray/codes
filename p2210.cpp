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
int n, ans, fd[15][5], pos[15];
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
Int randint(int l, int r){
    return rand() % (r-l+1) + l;
}
int main(){
    srand(time(0));
    input(n);
    for(ri i = 1; i <= n; i++) for(ri j = 0; j < 3; j++) input(fd[i][j]);
    for(ri i = 1; i <= n; i++) pos[i] = i;
    ans = 0x7fffffff;
    for(ri times = 0; times < 300; times++){
        for(register db T = 10000; T > 1e-12; T *= 0.99){
            int x = randint(1, n), y = randint(1, n);
            while(x == y) x = randint(1, n), y = randint(1, n);
            swap(pos[x], pos[y]);
            int totCost = 0;
            for(ri i = 1; i <= n; i++) for(ri j = 0; j < 3; j++) totCost += abs(pos[i] - pos[fd[i][j]]);
            totCost /= 2;
            if(totCost < ans) ans = totCost;
            else if(exp(ans-totCost) / T > (double)rand() / RAND_MAX) swap(pos[x], pos[y]);
        }
    }
    write(ans);
	return 0;
}