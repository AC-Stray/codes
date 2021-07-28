#include<bits/stdc++.h>
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const double eps = 1e-10;
const int MOD = 998244353;
const int N = 1005;
int n, cnt, pos[N<<1], k;
bool covered[N];
double ans;
struct circle{
	int x, y, r;
}cir[N], c[N];
template<typename T>
T read(){
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
Bool cmp(circle a, circle b){
	return a.r > b.r;
}
inline double dis(int x1, int y1, int x2, int y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
Bool cover(circle a, circle b){
	return dis(a.x, a.y, b.x, b.y) + b.r <= a.r;
}
inline double f(double x){
	vector< pair<double, double> > p;
	for(ri i = 0; i < cnt; i++){
		if(fabs(x-c[i].x) < c[i].r){
			double dis = sqrt(c[i].r*c[i].r - fabs(x-c[i].x)*fabs(x-c[i].x));
			p.emplace_back(c[i].y - dis, c[i].y + dis);
		}
	}
	if(p.empty()) return 0;
	sort(p.begin(), p.end());
	double start = p[0].first, end = p[0].second, ans = 0;
	for(ri i = 1; i < p.size(); i++){
		if(p[i].first > end) ans += end - start, start = p[i].first, end = p[i].second;
		else end = max(end, p[i].second);
	}
	ans += end - start;
	return ans;
}
inline double calc(double l, double r){
	return (r - l) * (f(l) + 4*f((l+r)/2) + f(r)) / 6;
}
double simpson(double l, double r, double ans){
	double mid = (l + r) / 2;
	double left = calc(l, mid), right = calc(mid, r);
	if(fabs(left+right-ans) < eps) return left + right;
	else return simpson(l, mid, left) + simpson(mid, r, right);
}
int main(){
	input(n);
	for(ri i = 0; i < n; i++){
		input(cir[i].x, cir[i].y, cir[i].r);
		pos[i<<1]   = cir[i].x - cir[i].r;
		pos[i<<1|1] = cir[i].x + cir[i].r;
	}
	sort(cir, cir + n, cmp);
	for(ri i = 0; i < n; i++){
		if(!covered[i]) c[cnt++] = cir[i];
		for(ri j = i + 1; j < n; j++) if(cover(cir[i], cir[j])) covered[j] = true;
	}
	sort(pos, pos + (n<<1));
	k = unique(pos, pos + (n<<1)) - pos;
	for(ri i = 1; i < k; i++) ans += simpson(pos[i-1], pos[i], calc(pos[i-1], pos[i]));
	cout << fixed << setprecision(3) << ans;
	return 0;
}

