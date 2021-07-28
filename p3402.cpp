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
int n, m, opt, a, b, nv, sfa[100005], vc[200005];
rope<int> *fa[200005];
Int get(int x, int ver){
    if(fa[ver]->at(x) == x) return x;
    else{
        int tmp = get(fa[ver]->at(x), ver);
        if(tmp == fa[ver]->at(x)) return tmp;
        fa[ver]->replace(x, tmp);
        return tmp;
    }
}
Void unite(int x, int y, int ver){
    int f1, f2;
    f1 = get(x, ver);
    f2 = get(y, ver);
    fa[ver]->replace(f1, f2);
}
Bool isSame(int x, int y, int ver){
    int f1, f2;
    f1 = get(x, ver);
    f2 = get(y, ver);
    return f1 == f2;
}
int main(){
    freopen("input.in", "r", stdin);
    scanf("%d %d", &n, &m);
    for(ri i = 1; i <= n; i++) sfa[i] = i;
    nv = 0;
    fa[nv] = new rope<int> (sfa, sfa+n+1);
    for(ri i = 1; i <= m; i++){
        scanf("%d", &opt);
        if(opt == 1){
            scanf("%d %d", &a, &b);
            if(isSame(a, b, vc[i-1])) vc[i] = vc[i-1];
            else{
                vc[i] = ++nv;
                fa[nv] = new rope<int> (*fa[vc[i-1]]);
                unite(a, b, vc[i]);
            }
        }
        else if(opt == 2){
            scanf("%d", &a);
            vc[i] = vc[a];
        }
        else{
            vc[i] = vc[i-1];
            scanf("%d %d", &a, &b);
            cout << isSame(a, b, vc[i]) << endl;
        }
    }
	return 0;
}