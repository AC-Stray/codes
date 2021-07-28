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
	const int BIG_INT_SIZE = 100005;
	const int BIG_INT_BASE = 10;
	struct bigint{
		int v[BIG_INT_SIZE], size;
		bigint(): size(0) { memset(v, 0, sizeof(v)); }
		bigint(int size): size(size) { memset(v, 0, sizeof(v)); }
		void print() { for(ri i = size - 1; i >= 0; i--) putchar(v[i]+'0'); }
		int& operator [] (const int &index) { return v[index]; }
		int operator [] (const int &index) const { return v[index]; }
		void operator = (const bigint &b){
			size = b.size;
			for(ri i = 0; i < size; i++) v[i] = b[i];
		}
		void operator = (ll x){
			size = 0;
			while(x){
				v[size++] = x % BIG_INT_BASE;
				x /= BIG_INT_BASE;
			}
		}
		bigint operator + (const bigint &b){
			bigint res(max(size, b.size));
			for(ri i = 0; i < res.size; i++) res[i] = v[i] + b[i];
			for(ri i = 0; i < res.size; i++){
				res[i+1] += res[i] / BIG_INT_BASE;
				res[i] %= BIG_INT_BASE;
				if(res[res.size]) res.size++;
			}
			return res;
		}
		bigint operator + (int b){
			bigint res(size);
			for(ri i = 0; i < res.size; i++){
				res[i] = v[i] + b % BIG_INT_BASE;
				b /= BIG_INT_BASE;
			}
			for(ri i = 0; i < res.size; i++){
				res[i+1] += res[i] / BIG_INT_BASE;
				res[i] %= BIG_INT_BASE;
				if(res[res.size]) res.size++;
			}
			return res;
		}
		bigint operator - (const bigint &b){
			bigint res(max(size, b.size));
			for(ri i = 0; i < res.size; i++) res[i] = v[i] - b[i];
			for(ri i = 0; i < res.size; i++){
				if(res[i] < 0){
					res[i+1]--;
					res[i] += BIG_INT_BASE;
				}
			}
			for(ri i = res.size - 1; i >= 0 && res[i] == 0; i--) res.size--;
			return res;
		}
		bigint operator * (const int &b){
			bigint res = *this;
			for(ri i = 0; i < res.size; i++) res[i] = v[i] * b;
			for(ri i = 0; i < res.size; i++){
				res[i+1] += res[i] / BIG_INT_BASE;
				res[i] %= BIG_INT_BASE;
				if(res[res.size]) res.size++;
			}
			return res;
		}
	}ans, lans, Lans;
	int n;
	void Main(){
		input(n);
		if(n == 1) return puts("1"), void();
		if(n == 2) return puts("5"), void();
		ans = 5, lans = 1;
		for(ri i = 3; i <= n; i++){
			Lans = lans;
			lans = ans;
			ans = lans * 3 - Lans + 2;
		}
		ans.print();
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

