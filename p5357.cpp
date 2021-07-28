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
const int N = 200005;
const int L = 2000005;
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
	const int ACAM_SIZE = 200005;
	struct ACAM{
		int cnt, match[ACAM_SIZE], ch[ACAM_SIZE][30], fail[ACAM_SIZE];
		void clear(){
			cnt = 0;
			memset(ch, 0, sizeof(ch));
		}
		void build(char *s, int k){
			int len = strlen(s), p = 0;
			for(ri i = 0; i < len; i++){
				if(!ch[p][s[i]-'a']) ch[p][s[i]-'a'] = ++cnt;
				p = ch[p][s[i]-'a'];
			}
			match[k] = p;
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
	int n, siz[N];
	char s[L];
	vector<int> g[N];
	void dfs(int u){
		for(ri i = 0; i < g[u].size(); i++){
			int v = g[u][i];
			dfs(v);
			siz[u] += siz[v];
		}
	}
	void Main(){
		AC.clear();
		input(n);
		for(ri i = 0; i < n; i++) scanf("%s", s), AC.build(s, i);
		AC.getfail();
		for(ri i = 1; i <= AC.cnt; i++) g[AC.fail[i]].push_back(i);
		scanf("%s", s);
		int len = strlen(s);
		for(ri i = 0, p = 0; i < len; i++){
			p = AC.ch[p][s[i]-'a'];
			siz[p]++;
		} 
		dfs(0);
		for(ri i = 0; i < n; i++) write(siz[AC.match[i]]), puts("");
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

