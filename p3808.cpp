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
const int N = 1000005;
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
	const int ACAM_SIZE = 2000005;
	struct ACAM{
		int cnt, num[ACAM_SIZE], fail[ACAM_SIZE], ch[ACAM_SIZE][30];
		ACAM(){
			cnt = 0;
			memset(ch, 0, sizeof(ch));
			memset(num, 0, sizeof(num));
		}
		void build(char *s){
			int len = strlen(s), p = 0;
			for(ri i = 0; i < len; i++){
				if(!ch[p][s[i]-'a']) ch[p][s[i]-'a'] = ++cnt;
				p = ch[p][s[i]-'a'];
			}
			num[p]++;
		}
		void getfail(){
			queue<int> q;
			for(ri i = 0; i < 26; i++){
				if(ch[0][i]){
					q.push(ch[0][i]);
					fail[ch[0][i]] = 0;
				}
			}
			while(!q.empty()){
				int now = q.front(); q.pop();
				for(ri i = 0; i < 26; i++){
					int p = ch[now][i];
					if(p){
						fail[p] = ch[fail[now]][i];
						q.push(p);
					}
					else ch[now][i] = ch[fail[now]][i];
				}
			}
		}
		int solve(char *s){
			int len = strlen(s), p = 0, ans = 0;;
			for(ri i = 0; i < len; i++){
				p = ch[p][s[i]-'a'];
				for(ri j = p; j && num[j] != -1; j = fail[j]) ans += num[j], num[j] = -1;
			}
			return ans;
		}
	}AC;
	int n;
	char str[N];
	void Main(){
		input(n);
		for(ri i = 0; i < n; i++){
			scanf("%s", str);
			AC.build(str);
		}
		AC.getfail();
		scanf("%s", str);
		write(AC.solve(str));
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

