#include<bits/stdc++.h>
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 5e4 + 5;
int n, top, stop, ans;
struct Vector{
	int x, y;
	Vector() {}
	Vector(int x, int y): x(x), y(y) {}
}point[N], stk[N], S[N];
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
void input(Type& arg, Types&... args){
	arg = read<Type>();
	input(args...);
}
Bool cmp(Vector a, Vector b){
	return a.x == b.x ? a.y < b.y : a.x < b.x;
}
inline int dis(Vector a, Vector b){
	return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
Int cross(Vector a, Vector b){
	return a.x * b.y - a.y * b.x;
}
Int side(Vector a, Vector b, Vector c){
	Vector t1(b.x - a.x, b.y - a.y);
	Vector t2(c.x - a.x, c.y - a.y);
	return cross(t1, t2);
}
int main(){
	input(n);
	for(ri i = 0; i < n; i++) input(point[i].x, point[i].y);
	sort(point, point + n, cmp);
	stk[0] = point[0], stk[1] = point[1];
	top = 2;
	for(ri i = 2; i < n; i++){
		while(top > 1 && side(stk[top-2], stk[top-1], point[i]) >= 0) top--;
		stk[top] = point[i];
	}
	for(ri i = 0; i < top; i++) S[i] = stk[i];
	stop = top;
	stk[0] = point[0], stk[1] = point[n-2];
	top = 2;
	for(ri i = 2; i < n; i++){
		while(top > 1 && side(stk[top-2], stk[top-1], point[i]) <= 0) top--;
		stk[top] = point[i];
	}
	for(ri i = 1; i < top-1; i++) S[stop+i-2] = stk[i];
	stop += top - 2;
	S[stop] = S[0];
	if(stop == 2) return write(dis(S[0], S[1])), 0;
	ri j = 2;
	for(ri i = 0; i < stop; i++){
		while(side(S[i], S[i+1], S[j]) < side(S[i], S[i+1], S[(j+1)%stop])) j = (j + 1) % stop;
		ans = max(ans, max(dis(S[i], S[j]), dis(S[i], S[(j+1)%stop])));
	}
	write(ans);
	return 0;
}
