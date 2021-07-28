#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define Char inline char
#define LL inline long long
#define DB inline double
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
ll n, ming, v, away;
char opt;
vector<int> people;
LL read(){
	ll n = 0; int f = 1; char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') f *= -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		n = (n << 1) + (n << 3) + ch-'0';
		ch = getchar();
	}
	return f * n;
}
Void write(ll n){
	if(n/10) write(n/10);
	putchar(n%10+'0');
}
int main(){
    freopen("input.in", "r", stdin);
	n = read(), ming = read();
	while(n--){
		cin >> opt;
		switch(opt){
			case 'I':
				v = read();
				if(v < ming) break;
				people.insert(lower_bound(people.begin(), people.end(), v, greater<int>()), v);
				break;
			case 'A':
                v = read();
				for(ri i = 0; i < people.size(); i++) people[i] += v;
				break;
			case 'S':
                v = read();
				for(ri i = 0; i < people.size(); i++) people[i] -= v;
		        for(ri i = people.size()-1; i >= 0; i--)
			        if(people[i] < ming) people.erase(people.begin()+i), away++;
			        else break;
				break;
			case 'F':
				v = read();
				if(v > people.size()){
					puts("-1");
					break;
				}
				write(people[v-1]);
				puts("");
		        for(ri i = people.size()-1; i >= 0; i--)
			        if(people[i] < ming) people.erase(people.begin()+i), away++;
			        else break;
				break;
		}
	}
	write(away);
	return 0;
}