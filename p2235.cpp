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
const int N = 505;
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
	const int base = 1e8;
	const int BIGINT_SIZE = 100;
	int aux[BIGINT_SIZE << 3];
	struct bigint {
		int s[BIGINT_SIZE], l;
		void CL() { l = 0; memset(s, 0, sizeof(s)); }
		void pr()
		{
			printf("%d", s[l]);
			for (int i = l - 1; i; i--)
				printf("%08d", s[i]);
		}
		void re_l()
		{
			int i, x = 0, k = 1, L = 0, fl, o;
			char c = getchar();
			for (; c < '0' || c > '9'; c = getchar());
			for (; c >= '0' && c <= '9'; c = getchar())
			{
				if (!(L - 1) && !aux[L])
					L--;
				aux[++L] = c - '0';
			}
			CL();
			l = L / 8 + ((o = L % 8) > 0);
			for (i = 1; i <= o; i++)
				x = x * 10 + aux[i];
			if (o)
				s[l] = x;
			for (fl = !o ? l + 1 : l, i = o + 1, x = 0; i <= L; i++, k++)
			{
				x = x * 10 + aux[i];
				if (!(k ^ 8))
					s[--fl] = x, x = k = 0;
			}
			if (!l)
				l = 1;
		}
		ll toint()
		{
			ll x = 0;
			for (int i = l; i; i--)
				x = x * base + s[i];
			return x;
		}
		bigint operator = (int b)
		{
			CL();
			do
			{
				s[++l] = b % base;
				b /= base;
			} while (b > 0);
			return *this;
		}
		bigint operator = (ll b)
		{
			CL();
			do
			{
				s[++l] = b % base;
				b /= base;
			} while (b > 0);
			return *this;
		}
		bigint operator + (const int& b)
		{
			bigint c = *this;
			ll x = b;
			for (int i = 1; i <= l && x; i++)
			{
				x = x + c.s[i];
				c.s[i] = x % base;
				x /= base;
			}
			if (x)
				c.s[++c.l] = x;
			return c;
		}
		bigint operator + (const ll & b)
		{
			bigint c = *this;
			ll x = b;
			for (int i = 1; i <= l && x; i++)
			{
				x = x + c.s[i];
				c.s[i] = x % base;
				x /= base;
			}
			if (x)
				c.s[++c.l] = x;
			return c;
		}
		bigint operator + (bigint & b)
		{
			if (b.l < 3)
				return *this + b.toint();
			bigint c;
			ll x = 0;
			int k = l < b.l ? b.l : l;
			c.CL(); c.l = k;
			for (int i = 1; i <= k; i++)
			{
				x = x + s[i] + b.s[i];
				c.s[i] = x % base;
				x /= base;
			}
			if (x)
				c.s[++c.l] = x;
			return c;
		}
		bigint operator - (const bigint & b)
		{
			bigint c, d = *this;
			ll x = 0;
			c.CL();
			for (int i = 1; i <= l; i++)
			{
				if ((x = d.s[i]) < b.s[i])
				{
					d.s[i + 1]--;
					x += base;
				}
				c.s[i] = x - b.s[i];
			}
			c.l = l;
			for (; !c.s[c.l] && c.l > 1; c.l--);
			return c;
		}
		bigint operator - (const int& b) { bigint c; return *this - (c = b); }
		bigint operator - (const ll & b) { bigint c; return *this - (c = b); }
		bigint operator * (const int& b)
		{
			bigint c;
			ll x = 0;
			c.CL();
			for (int i = 1; i <= l; i++)
			{
				x = x + 1LL * s[i] * b;
				c.s[i] = x % base;
				x /= base;
			}
			for (c.l = l; x; x /= base)
				c.s[++c.l] = x % base;
			return c;
		}
		bigint operator * (bigint & b)
		{
			if (b.l < 2)
				return *this * b.toint();
			bigint c;
			ll x;
			int i, j, k;
			c.CL();
			for (i = 1; i <= l; i++)
			{
				x = 0;
				for (j = 1; j <= b.l; j++)
				{
					x = x + 1LL * s[i] * b.s[j] + c.s[k = i + j - 1];
					c.s[k] = x % base;
					x /= base;
				}
				if (x)
					c.s[i + b.l] = x;
			}
			for (c.l = l + b.l; !c.s[c.l] && c.l > 1; c.l--);
			return c;
		}
		bigint operator * (const ll & b)
		{
			bigint c;
			if (b > 2e9)
			{
				c = b;
				return *this* c;
			}
			ll x = 0;
			c.CL();
			for (int i = 1; i <= l; i++)
			{
				x = x + b * s[i];
				c.s[i] = x % base;
				x /= base;
			}
			for (c.l = l; x; x /= base)
				c.s[++c.l] = x % base;
			return c;
		}
		bigint operator / (const int& b)
		{
			bigint c;
			ll x = 0;
			c.CL();
			for (int i = l; i; i--)
			{
				c.s[i] = (x * base + s[i]) / b;
				x = (x * base + s[i]) % b;
			}
			for (c.l = l; !c.s[c.l] && c.l > 1; c.l--);
			return c;
		}
		bigint operator / (const ll & b)
		{
			bigint c;
			ll x = 0;
			c.CL();
			for (int i = l; i; i--)
			{
				c.s[i] = (x * base + s[i]) / b;
				x = (x * base + s[i]) % b;
			}
			for (c.l = l; !c.s[c.l] && c.l > 1; c.l--);
			return c;
		}
		bigint operator / (bigint & b)
		{
			if (b.l < 2)
				return *this / b.toint();
			bigint c, d;
			int i, j, le, r, mid, k;
			c.CL(); d.CL();
			for (i = l; i; i--)
			{
				for (j = ++d.l; j > 1; j--)
					d.s[j] = d.s[j - 1];
				d.s[1] = s[i];
				if (d < b)
					continue;
				le = k = 0; r = base - 1;
				while (le <= r)
				{
					mid = (le + r) >> 1;
					b * mid <= d ? le = mid + 1, k = mid : r = mid - 1;
				}
				c.s[i] = k; d = d - b * k;
			}
			for (c.l = l; !c.s[c.l] && c.l > 1; c.l--);
			return c;
		}
		bigint operator % (const int& b)
		{
			bigint c;
			ll x = 0;
			c.CL();
			for (int i = l; i; i--)
				x = (x * base + s[i]) % b;
			return c = x;
		}
		bigint operator % (const ll & b)
		{
			bigint c;
			ll x = 0;
			c.CL();
			for (int i = l; i; i--)
				x = (x * base + s[i]) % b;
			return c = x;
		}
		bigint operator % (bigint & b)
		{
			if (b.l < 2)
				return *this % b.toint();
			bigint c;
			int i, j, le, r, mid, k;
			c.CL();
			for (i = l; i; i--)
			{
				for (j = ++c.l; j > 1; j--)
					c.s[j] = c.s[j - 1];
				c.s[1] = s[i];
				if (c < b)
					continue;
				le = k = 0; r = base - 1;
				while (le <= r)
				{
					mid = (le + r) >> 1;
					b * mid <= c ? le = mid + 1, k = mid : r = mid - 1;
				}
				c = c - b * k;
			}
			for (; !c.s[c.l] && c.l > 1; c.l--);
			return c;
		}
		bigint operator += (bigint & b) { return *this = *this + b; }
		bigint operator += (ll b) { return *this = *this + b; }
		bigint operator += (int b) { return *this = *this + b; }
		bigint operator -= (bigint & b) { return *this = *this - b; }
		bigint operator -= (ll b) { return *this = *this - b; }
		bigint operator -= (int b) { return *this = *this - b; }
		bigint operator *= (bigint & b) { return *this = *this * b; }
		bigint operator *= (ll b) { return *this = *this * b; }
		bigint operator *= (int b) { return *this = *this * b; }
		bigint operator /= (bigint & b) { return *this = *this / b; }
		bigint operator /= (ll b) { return *this = *this / b; }
		bigint operator /= (int b) { return *this = *this / b; }
		bigint operator %= (bigint & b) { return *this = *this % b; }
		bigint operator %= (ll b) { return *this = *this % b; }
		bigint operator %= (int b) { return *this = *this % b; }
		bool operator < (const bigint & b) const
		{
			if (l ^ b.l)
				return l < b.l;
			for (int i = l; i; i--)
				if (s[i] ^ b.s[i])
					return s[i] < b.s[i];
			return false;
		}
		bool operator <= (const bigint & b) const
		{
			if (l ^ b.l)
				return l < b.l;
			for (int i = l; i; i--)
				if (s[i] ^ b.s[i])
					return s[i] < b.s[i];
			return true;
		}
		bool operator > (const bigint & b) const
		{
			if (l ^ b.l)
				return l > b.l;
			for (int i = l; i; i--)
				if (s[i] ^ b.s[i])
					return s[i] > b.s[i];
			return false;
		}
		bool operator >= (const bigint & b) const
		{
			if (l ^ b.l)
				return l > b.l;
			for (int i = l; i; i--)
				if (s[i] ^ b.s[i])
					return s[i] > b.s[i];
			return true;
		}
		bool operator == (const bigint & b) const
		{
			if (l ^ b.l)
				return false;
			for (int i = l; i; i--)
				if (s[i] ^ b.s[i])
					return false;
			return true;
		}
		bool operator != (const bigint & b) const
		{
			if (l ^ b.l)
				return true;
			for (int i = l; i; i--)
				if (s[i] ^ b.s[i])
					return true;
			return false;
		}
		bool operator < (ll b) const { bigint c; return *this < (c = b); }
		bool operator <= (ll b) const { bigint c; return *this <= (c = b); }
		bool operator > (ll b) const { bigint c; return *this > (c = b); }
		bool operator >= (ll b) const { bigint c; return *this >= (c = b); }
		bool operator == (ll b) const { bigint c; return *this == (c = b); }
		bool operator != (ll b) const { bigint c; return *this != (c = b); }
		bool operator < (int b) const { bigint c; return *this < (c = b); }
		bool operator <= (int b) const { bigint c; return *this <= (c = b); }
		bool operator > (int b) const { bigint c; return *this > (c = b); }
		bool operator >= (int b) const { bigint c; return *this >= (c = b); }
		bool operator == (int b) const { bigint c; return *this == (c = b); }
		bool operator != (int b) const { bigint c; return *this != (c = b); }
	};
	int num[N], tmp[N], len;
	bigint m, dp[2][N][N];
	bool mark[2][N][N];
	bigint dfs(int pos, int st, bool flag, bool limit){
		bigint res, t; res = 0;
		if(pos < 1) return (flag && st > 0) ? res = 1 : res;
		if(!limit && mark[flag][pos][st]) return dp[flag][pos][st];
		int ed = limit ? num[pos] : 1;
		for(ri i = 0; i <= ed; i++){
			tmp[pos] = i;
			if(pos == st && i == 0) res += t = dfs(pos-1, st-1, flag, limit&&i==num[pos]);
			else res += t = dfs(pos-1, st, flag&&pos<=(st>>1)?i==tmp[st-pos+1]:flag, limit&&i==num[pos]);
		}
		return mark[flag][pos][st] = true, dp[flag][pos][st] = res;
	} 
	void Main(){
		m.re_l();
		while(m > 0){
			num[++len] = (m % 2).toint();
			m /= 2;
		}
		dfs(len, len, true, true).pr();
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

