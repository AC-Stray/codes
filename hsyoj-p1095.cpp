#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
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
	const int N = 5005;
	int n, m, c, lim[N];
	ll f[N], ans[N], lst[N];
	bool task1 = true, task2 = true;
	struct object{
		int v, w;
		object()  {}
		object(int v, int w): v(v), w(w) {}
	};
	vector<object> obj[N];
	struct typeObject{
		int v, w, c;
		typeObject() {}
		typeObject(int v, int w, int c): v(v), w(w), c(c) {}
		bool operator < (const typeObject &b) const { return v > b.v; }
	};
	vector<typeObject> tobj;
	void solve1(){
		cerr << "[solve1]" << endl;
		sort(tobj.begin(), tobj.end());
		for(ri i = 0; i < tobj.size() && m; i++){
			if(!lim[tobj[i].c]) continue;
			lim[tobj[i].c]--, m--;
			ans[0] += tobj[i].v;
		}
		write(ans[0]);
	}
	void solve2(){
		cerr << "[solve2]" << endl;
		for(ri i = 0; i < tobj.size(); i++){
			for(ri j = m; j >= tobj[i].w; j--){
				ans[j] = max(ans[j], ans[j-tobj[i].w] + tobj[i].v);
			}
		}
		write(ans[m]);
	}
	void Main(){
		n = read<int>(), m = read<int>(), c = read<int>();
		for(ri i = 0, v, w, t; i < n; i++){
			v = read<int>(), w = read<int>(), t = read<int>();
			obj[t].push_back(object(v, w));
			tobj.push_back(typeObject(v, w, t));
			task1 &= w == 1;
		}
		for(ri i = 1; i <= c; i++){
			lim[i] = min(m, read<int>());
			task2 &= lim[i] == m;
		}
		if(task1) return solve1();
		if(task2) return solve2();
		for(ri i = 1; i <= c; i++){
			memset(f, 0, sizeof(f));
			for(ri j = 0; j < obj[i].size(); j++){
				for(ri k = lim[i]; k >= obj[i][j].w; k--){
					f[k] = max(f[k], f[k-obj[i][j].w] + obj[i][j].v);
				}
			}
			memcpy(lst, ans, sizeof(ans));
			for(ri j = 0; j <= lim[i]; j++){
				for(ri k = 0; j + k <= m; k++){
					ans[j+k] = max(ans[j+k], lst[k] + f[j]);
				}
			}
		}
		write(ans[m]);
		return;
	}
}
int main(){
//	File(diversity)
	Main::Main();
	return 0;
}
