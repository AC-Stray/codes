#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const ll infll = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-10;
const int N = 100005;
const int L = 1000005;
template<typename T>
inline T read(){
	T n = 0; int f = 1; char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') f = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		n = n * 10 + ch - '0';
		ch = getchar();
	}
	return f * n;
}
template<typename T>
void write(T n){
	if(n/10) write(n/10);
	putchar(n%10+'0');
}
void input() {}
template<typename Type, typename... Types>
void input(Type &arg, Types&... args){
	arg = read<Type>();
	input(args...);
}
namespace Main{
	int n, m, len, dfnCnt, a[N], ans[N], dfn[N], dfn2[N];
	char s[L];
	vector<int> g[N];
	vector<pii> ask[N];
	const int ACAM_SIZE = 100005;
	struct ACAM{
		int cnt, fa[ACAM_SIZE], ch[ACAM_SIZE][30], fail[ACAM_SIZE];
		void build(){
			int p = 0;
			for(ri i = 0; i < len; i++){
				if(islower(s[i])){
					if(!ch[p][s[i]-'a']) ch[p][s[i]-'a'] = ++cnt;
					fa[ch[p][s[i]-'a']] = p;
					p = ch[p][s[i]-'a'];
				}
				else if(s[i] == 'B') p = fa[p];
				else if(s[i] == 'P') a[++n] = p;
			}
		}
		void getfail(){
			queue<int> q;
			for(ri i = 0; i < 26; i++){
				if(ch[0][i]) fail[ch[0][i]] = 0, q.push(ch[0][i]);
				else fail[ch[0][i]] = 0;
			}
			while(!q.empty()){
				int now = q.front(); q.pop();
				for(ri i = 0; i < 26; i++){
					if(ch[now][i]){
						fail[ch[now][i]] = ch[fail[now]][i];
						q.push(ch[now][i]);
					}
					else ch[now][i] = ch[fail[now]][i];
				}
			}
		}
	}AC;
	struct bintree{
		int n, a[N];
		bintree() { memset(a, 0, sizeof(a)); }
		int lowbit(int x) { return x & -x; }
		void add(int x, int v) { for(ri i = x; i <= n; i += lowbit(i)) a[i] += v; }
		int query(int x) { int res = 0; for(ri i = x; i > 0; i -= lowbit(i)) res += a[i]; return res; }
	}tree;
	void dfs(int u){
		dfn[u] = ++dfnCnt;
		for(ri i = 0; i < g[u].size(); i++){
			int v = g[u][i];
			dfs(v);
		}
		dfn2[u] = dfnCnt;
	}
	void Main(){
		scanf("%s", s);
		len = strlen(s);
		AC.build();
		AC.getfail();
		for(ri i = 1; i <= AC.cnt; i++) g[AC.fail[i]].push_back(i);
		dfs(0);
		input(m);
		for(ri i = 0, x, y; i < m; i++) input(x, y), ask[y].push_back(make_pair(i, x));
		tree.n = dfnCnt;
		for(ri i = 0, j = 0, p = 0; i < len; i++){
			if(islower(s[i])) p = AC.ch[p][s[i]-'a'], tree.add(dfn[p], 1);
			else if(s[i] == 'B') tree.add(dfn[p], -1), p = AC.fa[p];
			else if(s[i] == 'P'){
				j++;
				for(ri k = 0; k < ask[j].size(); k++){
					pii now = ask[j][k];
					ans[now.first] = tree.query(dfn2[a[now.second]]) - tree.query(dfn[a[now.second]]-1);
				} 
			}
		}
		for(ri i = 0; i < m; i++) write(ans[i]), puts("");
		return;
	}
} // namespace
int main(){
#ifdef Liuxizai
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif // Liuxizai
	Main::Main();
	return 0;
}

