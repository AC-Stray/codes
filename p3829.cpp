#include<bits/stdc++.h>
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const double pi = acos(-1);
const int N = 10005;
int n, top;
double a, b, r, x, y, theta, ans;
struct Vector{
	double x, y;
	Vector() {}
	Vector(double x, double y): x(x), y(y) {}
	Vector operator + (const Vector &b) { return Vector(x + b.x, y + b.y); }
}point[N<<2], stk[N<<2];
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
Bool cmp(Vector a, Vector b){
	return a.x == b.x ? a.y < b.y : a.x < b.x;
}
inline double dis(Vector a, Vector b){
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}
inline double cross(Vector a, Vector b){
	return a.x * b.y - b.x * a.y;
}
inline double side(Vector a, Vector b, Vector c){
	Vector t1 = Vector(b.x - a.x, b.y - a.y);
	Vector t2 = Vector(c.x - a.x, c.y - a.y);
	return cross(t1, t2);
}
inline Vector rotate(Vector a, double t){
	double s = sin(t), c = cos(t);
	return Vector(a.x * c - a.y * s, a.x * s + a.y * c);
}
int main(){
	input(n);
	cin >> a >> b >> r;
	swap(a, b);
	for(ri i = 0; i < n; i++){
		cin >> x >> y >> theta;
		point[i<<2]   = rotate(Vector( a / 2 - r,  b / 2 - r), theta) + Vector(x, y);
		point[i<<2|1] = rotate(Vector( a / 2 - r, -b / 2 + r), theta) + Vector(x, y);
		point[i<<2|2] = rotate(Vector(-a / 2 + r,  b / 2 - r), theta) + Vector(x, y);
		point[i<<2|3] = rotate(Vector(-a / 2 + r, -b / 2 + r), theta) + Vector(x, y);		
	}
	ans = 2 * r * pi;
	n <<= 2;
	sort(point, point + n, cmp);
	stk[0] = point[0], stk[1] = point[1];
	top = 2;
	for(ri i = 2; i < n; i++){
		while(top > 1 && side(stk[top-2], stk[top-1], point[i]) >= 0) top--;
		stk[top++] = point[i];
	}
	for(ri i = 1; i < top; i++) ans += dis(stk[i-1], stk[i]);
	stk[0] = point[0], stk[1] = point[1];
	top = 2;
	for(ri i = 2; i < n; i++){
		while(top > 1 && side(stk[top-2], stk[top-1], point[i]) <= 0) top--;
		stk[top++] = point[i];
	}
	for(ri i = 1; i < top; i++) ans += dis(stk[i-1], stk[i]);
	cout << fixed << setprecision(2) << ans << endl;
	return 0;
}

