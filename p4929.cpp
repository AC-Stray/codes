#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
int n, m;
namespace DLX{
    const int SIZE = 100005;
    const int N = 505;
    int res;
    int n, m, tot;
    int U[SIZE], D[SIZE], L[SIZE], R[SIZE];
    int first[N], siz[N];
    int col[SIZE], row[SIZE];
    int stk[N];
    void build(int r, int c){
        n = r, m = c;
        for(ri i = 0; i <= c; i++){
            L[i] = i - 1, R[i] = i + 1;
            U[i] = D[i] = i;
        }
        L[0] = c, R[c] = 0; tot = c;
        memset(first, 0, sizeof(first));
        memset(siz, 0, sizeof(siz));
    }
    void insert(int r, int c){
        col[++tot] = c, row[tot] = r; siz[c]++;
        D[tot] = D[c], U[D[c]] = tot; U[tot] = c, D[c] = tot;
        if(!first[r]) first[r] = tot, L[tot] = R[tot] = tot;
        else{
            R[tot] = R[first[r]], L[R[first[r]]] = tot;
            L[tot] = first[r], R[first[r]] = tot;
        }
    }
    void remove(int c){
        R[L[c]] = R[c], L[R[c]] = L[c];
        for(ri i = D[c]; i != c; i = D[i]) for(ri j = R[i]; j != i; j = R[j])
            U[D[j]] = U[j], D[U[j]] = D[j], siz[col[j]]--;
    }
    void recover(int c){
        for(ri i = U[c]; i != c; i = U[i]) for(ri j = L[i]; j != i; j = L[j])
            U[D[j]] = D[U[j]] = j, siz[col[j]]++;
        R[L[c]] = L[R[c]] = c;
    }
    bool dance(int step){
        if(R[0] == 0) return res = step, true;
        int c = R[0];
        for(ri i = R[0]; i != 0; i = R[i]) if(siz[i] < siz[c]) c = i;
        remove(c);
        for(ri i = D[c]; i != c; i = D[i]){
            stk[step] = row[i];
            for(ri j = R[i]; j != i; j = R[j]) remove(col[j]);
            if(dance(step+1)) return true;
            for(ri j = L[i]; j != i; j = L[j]) recover(col[j]);
        }
        recover(c);
        return false;
    }
}
LL read(){
	ll n = 0; int f = 1; char ch = getchar();
	while('0' > ch || ch > '9'){
		if(ch == '-') f *= -1;
		ch = getchar();
	}
	while('0' <= ch && ch <= '9'){
		n = (n << 1) + (n << 3) + ch-'0';
		ch = getchar();
	}
	return f * n;
}
Void write(ll x){
	if(x/10) write(x/10);
	putchar(x%10+'0');
}
Void input() {}
template<typename Type, typename... Types>
Void input(Type& arg, Types&... args){
    arg = read();
    input(args...);
}
int main(){
    input(n, m);
    DLX::build(n, m);
    for(ri i = 1; i <= n; i++) for(ri j = 1; j <= m; j++){
        int tmp; input(tmp);
        if(tmp == 1) DLX::insert(i, j);
    }
    DLX::dance(1);
    if(DLX::res) for(ri i = 1; i < DLX::res; i++) cout << DLX::stk[i] << ' ';
    else puts("No Solution!");
	return 0;
}