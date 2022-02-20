#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
#define int long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 100005;
int T, n, atk, sp, cnt, tot, buff, tag[N];
ll ans, mn;
bool at0;
vector<int> grp[N];
struct monster{
	ll at;
	int id, hp, tp;
	bool alive;
	bool operator < (const monster &b) const {
		if(alive == b.alive){
			if(hp == b.hp) return id < b.id;
			return hp < b.hp;
		}
		return alive > b.alive;
	}
}m[N];
struct bit{
	int v[N];
	Void init() { memset(v, 0, sizeof(v)); }
	Int lowbit(int x) { return x & -x; }
	void add(int x, int k) { for(; x < N; x += lowbit(x)) v[x] += k; }
	int query(int x) { int res = 0; for(; x; x -= lowbit(x)) res += v[x]; return res; }
}tree;
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
//LL needrd(int x, int rd){
//	return (m[x].hp - rd * atk - 1) / atk + 1;
//}
signed main(){
//	File(battle)
	T = read<int>();
	while(T--){
		tree.init();
		at0 = true, sp = tot = cnt = buff = ans = 0;
		n = read<int>(), atk = read<int>();
		for(ri i = 0; i < n; i++){
			m[i].id = i + 1;
			m[i].at = read<ll>();
			m[i].hp = read<int>();
			m[i].tp = read<int>();
			m[i].alive = true;
			if(m[i].at || m[i].tp & 2) at0 = false;
			if(m[i].tp & 1) sp++;
			if(m[i].tp & 2) buff += 2;
		}
		cerr << "Input " << (double)clock() / CLOCKS_PER_SEC << endl;
		
		while(sp){
			int nbf = 0;
			memset(tag, 0, sizeof(tag));
			for(ri i = 0; i < n; i++){
				if(!m[i].alive) continue;
				m[i].at += nbf;
				tag[i] = nbf;
				if(m[i].tp & 1){
					m[i].hp >>= 1;
					m[i].at <<= 1;
					if(!m[i].hp){
						m[i].alive = false;
						sp--;
						if(m[i].tp & 2) buff -= 2;
						if(m[i].tp & 4) nbf += 2;
						continue;
					}
				}
				ans += m[i].at + buff;
				m[i].hp -= atk;
				if(m[i].hp <= 0){
					m[i].alive = false;
					if(m[i].tp & 1) sp--;
					if(m[i].tp & 2) buff -= 2;
					if(m[i].tp & 4) nbf += 2;
				}
			}
			for(ri i = 0; i < n; i++) m[i].at += nbf - tag[i];
		}
		cerr << "Kill1 " << (double)clock() / CLOCKS_PER_SEC << endl;
		
		for(ri i = 0; i < n; i++){
			if(!m[i].alive) continue;
			tot += m[i].at;
			cnt++;
		}
		if(atk == 0){
			// hp decrease infinitely
			if(tot + cnt * buff > 0) puts("defeat");
			else write(ans), puts("");
			continue;
		}
		
		for(ri i = 1; i < N; i++) grp[i].clear();
		for(ri i = 0; i < n; i++){
			if(!m[i].alive) continue;
			tree.add(m[i].id, 1);
			m[i].hp = (m[i].hp - 1) / atk + 1;
			grp[m[i].hp].push_back(i);
		}
		for(ri i = 1; cnt; i++){
			ans += tot + cnt * buff;
			if(!grp[i].size()) continue;
			for(ri j = 0; j < grp[i].size(); j++){
				int x = grp[i][j];
				if(m[x].tp & 2) ans -= (cnt - tree.query(m[x].id)) << 1, buff -= 2;
				if(m[x].tp & 4) ans += (cnt - tree.query(m[x].id)) << 1, buff += 2;
				cnt--;
				tot -= m[x].at;
				tree.add(m[x].id, -1);
			}
		}
		cerr << "Final " << (double)clock() / CLOCKS_PER_SEC << endl;
//		==============================REFACTOR==============================
//		sort(m, m + n);
//		for(ri i = 0; i < n && m[i].alive; i++) tree.add(m[i].id, m[i].at), t2.add(m[i].id, 1);
//		int round = 0, p = 0;
//		cerr << (double)clock() / CLOCKS_PER_SEC << endl;
//		while(m[p].alive){
//			ll nrd = (m[p].hp - round * atk - 1) / atk + 1;
//			int ed = p;
//			while(needrd(ed, round) == nrd) ed++;
//			ans += (nrd - 1) * (tree.query(n) + t2.query(n) * buff);
//			ans += tree.query(m[p].id) + t2.query(m[p].id) * buff;
//			if(m[p].tp & 2) buff -= 2;
//			if(m[p].tp & 4) buff += 2;
//			tree.add(m[p].id, -m[p].at);
//			t2.add(m[p].id, -1);
//			while(p < ed - 1){
//				p++;
//				ans += tree.query(m[p].id) - tree.query(m[p-1].id) + (t2.query(m[p].id) - t2.query(m[p-1].id)) * buff;
//				if(m[p].tp & 2) buff -= 2;
//				if(m[p].tp & 4) buff += 2;
//				tree.add(m[p].id, -m[p].at);
//				t2.add(m[p].id, -1);
//			}
//			ans += tree.query(n) - tree.query(m[p].id) + (t2.query(n) - t2.query(m[p].id)) * buff;
//			round += nrd;
//			p = ed;
//		}
//		cerr << (double)clock() / CLOCKS_PER_SEC << endl;
//		==============================REFACTOR==============================
//		while(cnt){
//			mn = 0x7fffffff;
//			for(ri i = 0; i < n; i++) if(m[i].alive) mn = min(mn, m[i].at);
//			int round = (mn - 1) / atk + 1;
//			for(ri i = 0; i < n; i++){
//				if(!m[i].alive) continue;
//				ans += round * (m[i].at + buff);
//				m[i].hp -= round * atk;
//				if(m[i].hp <= 0){
//					m[i].alive = false;
//					cnt--;
//					tot -= m[i].at;
//					if(m[i].tp & 2) buff -= 2;
//					if(m[i].tp & 4) buff += 2;
//				}
//			}
//		}
		write(ans); puts("");
	}
	return 0;
}
