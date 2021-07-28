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
const int N = 205;
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
	pii ans[N];
	const int ACAM_SIZE = 100005;
	struct ACAM{
		int cnt, num[ACAM_SIZE], ch[ACAM_SIZE][30], fail[ACAM_SIZE];
		void clear(){
			cnt = 0;
			memset(num, 0, sizeof(num));
			memset(ch, 0, sizeof(ch));
		} 
		void build(char *s, int id){
			int len = strlen(s), p = 0;
			for(ri i = 0; i < len; i++){
				if(!ch[p][s[i]-'a']) ch[p][s[i]-'a'] = ++cnt;
				p = ch[p][s[i]-'a'];
			}
			num[p] = id;
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
					if(ch[now][i]) fail[ch[now][i]] = ch[fail[now]][i], q.push(ch[now][i]);
					else ch[now][i] = ch[fail[now]][i];
				}
			}
		}
		void solve(char *s){
			int len = strlen(s), p = 0;
			for(ri i = 0; i < len; i++){
				p = ch[p][s[i]-'a'];
				for(ri j = p; j; j = fail[j]) ans[num[j]].first++;
			}
		}
	}AC;
	int n;
	char a[N][105], s[L];
	Bool cmp(pii a, pii b){
		return a.first == b.first ? a.second < b.second : a.first > b.first;
	}
	void Main(){
		while(true){
			input(n);
			if(!n) break;
			AC.clear();
			for(ri i = 1; i <= n; i++){
				scanf("%s", a[i]);
				AC.build(a[i], i);
			}
			AC.getfail();
			for(ri i = 1; i <= n; i++) ans[i].first = 0, ans[i].second = i;
			scanf("%s", s);
			AC.solve(s);
			sort(ans + 1, ans + n + 1, cmp);
			write(ans[1].first); puts("");
			for(ri i = 1; i <= n && ans[i].first == ans[1].first; i++) puts(a[ans[i].second]);
		}
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

