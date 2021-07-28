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
#include<ext/rope>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
using namespace std;
using namespace __gnu_cxx;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
crope now, s[50005];
char str[1000005];
int n, len, d, opt, p, c, v;
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &opt);
		if(opt == 1){
			scanf("%d", &p);
			scanf("%s", str);
			p -= d;
			now.insert(p, str);
			s[++len] = now;
		}else if(opt == 2){
			scanf("%d %d", &p, &c);
			now.erase(p-1-d, c-d);
			s[++len] = now;
		}else {
			scanf("%d %d %d", &v, &p, &c);
			crope ans=s[v-d].substr(p-1-d, c-d);
			d+=count(ans.begin(), ans.end(),'c');
			cout << ans << endl;
		}
	}
    return 0;
}