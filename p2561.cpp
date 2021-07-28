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
int n;
struct big{
    int v[205], size;
    big() { size = 0; memset(v, 0, sizeof(v)); }
    friend ostream &operator << (ostream &output, const big x){
        for(int i = x.size-1; i >= 0; i--) output << x[i];
    	return output;
    }
    int& operator [] (const int index){
        return v[index];
    }
    int operator [] (const int index) const {
        return v[index];
    }
    void operator = (const int &b){
        size = 0;
        int t = b;
        while(t > 0){
            v[size++] = t % 10;
            t /= 10;
        }
    }
    void operator = (const big &b){
        size = b.size;
        for(ri i = 0; i < size; i++) v[i] = b[i];
    }
    big operator + (const big &b){
        big res;
        res.size = max(size, b.size);
        for(ri i = 0; i < res.size; i++) res[i] = v[i] + b[i];
        for(ri i = 0; i < res.size; i++){
            res[i+1] += res[i] / 10;
            res[i] %= 10;
            if(res[res.size]) res.size++;
        }
        return res;
    }
    big operator * (const int &b){
        big res;
        res.size = size;
        for(ri i = 0; i < res.size; i++) res[i] = v[i] * b;
        for(ri i = 0; i < res.size; i++){
            res[i+1] += res[i] / 10;
            res[i] %= 10;
            if(res[res.size]) res.size++;
        }
        return res;
    }
    big operator * (const big &b){
        big res;
        res.size = max(size, b.size);
        for(ri i = 0; i < res.size; i++) for(ri j = 0; j < res.size; j++)
            res[i+j] += v[i] * b[j];
        for(ri i = 0; i < res.size; i++){
            res[i+1] += res[i] / 10;
            res[i] %= 10;
            if(res[res.size]) res.size++;
        }
        return res;
    }
    big operator / (const int &b){
        big res;
        int rd = 0;
        for(ri i = size-1; i >= 0; i--){
            int t = rd * 10 + v[i];
            res[res.size++] = t / b;
            rd = t % b;
        }
        reverse(res.v, res.v+res.size);
        for(ri i = res.size-1; i >= 0 && res[i] == 0; i--) res.size--;
        return res;
    }
    big pow(int k){
        big rt, tmp;
        rt = 1;
        tmp = *this;
        while(k > 0){
            if(k & 1) rt = rt * tmp;
            tmp = tmp * tmp;
            k >>= 1;
        }
        return rt;
    }
};
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
    input(n);
    int m = n * (n+1) / 2, t = m%3==0?1:2;
    big two, ans;
    two = 2;
    ans = ans + two.pow(m/3+t) + two.pow(m) + two.pow(((n+1)*(n+1)+1)/4) * 3;
    ans = ans / 6;
    cout << ans;
	return 0;
}