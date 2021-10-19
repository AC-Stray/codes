#include<bits/stdc++.h>
#define ri /*register*/ int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int inf = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int N = 2005;
const int M = 205;
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
namespace Main{
	int n, m, cnt, siz[N*M], ch[N*M][26];
	char s[M];
	vector<ll> f[N*M];
	Void insert(){
		int p = 0, len = strlen(s);
		for(ri i = 0; i < len; i++){
			if(!ch[p][s[i]-'a']) ch[p][s[i]-'a'] = ++cnt;
			p = ch[p][s[i]-'a'];
		}
		siz[p]++;
	}
	void dfs(int u, int c){
		if(siz[u]){
			f[u].resize(siz[u] + 1);
			f[u][1] = c;
			return;
		}
		f[u] = {1};
		for(ri i = 0; i < 26; i++) if(ch[u][i]){
			int p = ch[u][i], cp = 1;
			while(!siz[p]){
				int flag = 0;
				for(ri i = 0; i < 26; i++) if(ch[p][i]){
					if(!flag) flag = ch[p][i];
					else { flag = 0; break; }
				}
				if(!flag) break;
				p = flag, cp++;
			}
			dfs(p, cp);
			vector<ll> tmp(siz[u] + siz[p] + 1);
			for(ri j = 0; j <= siz[u]; j++){
				for(ri k = 0; k <= siz[p]; k++){
					tmp[j+k] += f[u][j] * f[p][k] % MOD;
					tmp[j+k] %= MOD;
				}
			}
			siz[u] += siz[p];
			f[u] = tmp;
		}
		f[u][1] = (f[u][1] + c) % MOD;
	}
	void Main(){
		n = read<int>(), m = read<int>();
		for(ri i = 0; i < n; i++) { scanf("%s", s); insert(); }
		int p = 0, cp = 0;
		while(!siz[p]){
			int flag = 0;
			for(ri i = 0; i < 26; i++) if(ch[p][i]){
				if(!flag) flag = ch[p][i];
				else { flag = 0; break; }
			}
			if(!flag) break;
			p = flag, cp++;
		}
		dfs(p, cp);
		write(f[p][m]);
		return;
	}
}
int main(){
	Main::Main();
	return 0;
}
