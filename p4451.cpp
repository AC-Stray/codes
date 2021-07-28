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
const int sqrt2 = 59713600;
const int MOD = 1e9+7;
string n;
Void write(ll x){
	if(x/10) write(x/10);
	putchar(x%10+'0');
}
ll qpow(int a, int k){
    ll res = 1, tmp = a;
    while(k > 0){
        if(k&1) res = res * tmp % MOD;
        tmp = tmp * tmp % MOD;
        k >>= 1;
    }
    return res;
}
ll qpow(int a, string k){
    ll res = 1, tmp = a;
    while(k.size()){
        if((k[k.size()-1]-'0')&1) res = res * tmp % MOD;
        tmp = tmp * tmp % MOD;
        int rmd = 0;
        for(ri i = 0; i < k.size(); i++){
            int s = k[i]-'0';
            k[i] = (k[i]-'0' + rmd) / 2 + '0';
            rmd = s % 2 * 10;
            if(k[i] == '0' && i == 0) k.erase(k.begin()), i--;
        }
    }
    return res;
}
int main(){
    cin >> n;
    write((qpow(sqrt2+1, n) - qpow(1-sqrt2+MOD, n) + MOD) % MOD * qpow(2*sqrt2, MOD-2) % MOD);
	return 0;
}