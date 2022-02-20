#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define int long long
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
void input() {}
template<typename Type, typename... Types>
void input(Type& arg, Types&... args){
	arg = read<Type>();
	input(args...);
}
namespace Main{
	const int N = 100005;
	const unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
	mt19937 my_rand(seed);
	struct fhq_treap{
		int tot, root, ls[N], rs[N], pri[N], val[N], siz[N], st[N], sd[N];
		int alloc(int x) { tot++, ls[tot] = rs[tot] = 0, siz[tot] = 1, pri[tot] = my_rand(), val[tot] = x; return tot; }
		void pushup(int x) { siz[x] = siz[ls[x]] + siz[rs[x]] + 1; }
		void pushadd(int x, int s, int d) { val[x] += s + siz[ls[x]] * d, st[x] += s, sd[x] += d; }
		void pushdown(int x){
			pushadd(ls[x], st[x], sd[x]);
			pushadd(rs[x], st[x] + (siz[ls[x]] + 1) * sd[x], sd[x]);
			st[x] = 0, sd[x] = 0;
		}
		void split(int x, int k, int &L, int &R){
			if(x == 0) return L = R = 0, void();
			pushdown(x);
			if(siz[ls[x]] + 1 < k) L = x, split(rs[x], k - siz[ls[x]] - 1, rs[x], R);
			else R = x, split(ls[x], k, L, ls[x]);
			pushup(x);
		}
		int merge(int x, int y){
			if(!x || !y) return x | y;
			pushdown(x), pushdown(y);
			if(pri[x] >= pri[y]) return rs[x] = merge(rs[x], y), pushup(x), x;
			else return ls[y] = merge(x, ls[y]), pushup(y), y;
		}
		void insert(int x, int p){
			int L, R;
			split(root, p, L, R);
			root = merge(merge(L, alloc(x)), R);
		}
		void add(int x, int s, int d){
			int L, R;
			split(root, x, L, R);
			pushadd(R, s, d);
			root = merge(L, R);
		}
		int kth(int x, int k){
            while(true){
            	pushdown(x);
                if(k == siz[ls[x]] + 1) return val[x];
                if(k <= siz[ls[x]]) x = ls[x];
                else k -= siz[ls[x]] + 1, x = rs[x];
            }
        }
        int query(int x){
        	if(!x) return 0;
            pushdown(x);
        	return max(max(query(ls[x]), val[x]), query(rs[x]));
		}
		void print(int x){
			if(!x) return;
			pushdown(x);
			print(ls[x]);
			cout << val[x] << ' ';
			print(rs[x]);
		}
	}tree;
	int n, a[N];
	void Main(){
		input(n);
		for(int i = 1; i <= n; i++) input(a[i]);
		tree.root = tree.merge(tree.alloc(0), tree.alloc(a[1]));
		// tree.print(tree.root), cout << endl;
		for(int i = 2; i <= n; i++){
			int l = 2, r = i, res = i + 1;
			while(l <= r){
				int mid = l + r >> 1;
				if(tree.kth(tree.root, mid) <= tree.kth(tree.root, mid - 1) + (mid - 1) * a[i]) res = mid, r = mid - 1;
				else l = mid + 1;
			}
			tree.insert(tree.kth(tree.root, res - 1), res);
			tree.add(res, a[i] * (res - 1), a[i]);
			// tree.print(tree.root), cout << endl;
		}
		write(tree.query(tree.root));
		return;
	}
}
signed main(){
#ifdef Liuxizai
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
	Main::Main();
	return 0;
}
/*
6
123 -4655 11 -525 112 -444444
*/