#include<bits/stdc++.h>
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
int h, w, d;
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
int main(){
	input(h, w, d);
	for(ri i = 0; i < h; i++){
		for(ri j = 0; j < w; j++){
			switch(((((i+j)/d)&1)<<1)+(((i-j+w)/d)&1)){
				case 0: putchar('R'); break;
				case 1: putchar('Y'); break;
				case 2: putchar('G'); break;
				case 3: putchar('B'); break;
			}
		}
		puts("");
	}
	return 0;
}

