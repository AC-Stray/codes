#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
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
    const int N = 105;
    int n, ct, cs, lstt, lsts, tt[N], ts[N], val[N];
    int invC(int x){
        for(ri i = 2; ; i++)
            if(i * (i - 1) / 2 == x)
                return i;
    }
    void Main(){
        input(n, lstt, lsts);
        for(ri i = 1; i < n; i++){
            cout << "+ " << i << endl;
            input(ct, cs);
            tt[i] = ct - lstt, ts[i] = cs - lsts;
            lstt = ct, lsts = cs;
            if(tt[i]) val[i] = invC(tt[i]);
        }
        cout << "+ 1" << endl;
        input(tt[n], ts[n]);
        tt[n] -= lstt, ts[n] -= lsts;
        if(tt[n]) val[1] = invC(tt[n]) - 1;
        int delta = ts[n] - ts[1] - 1;
        if(val[2])          val[3] = delta - val[2];
        else if(val[3])     val[2] = delta - val[3];
        else if(delta == 0) val[2] = val[3] = 0;
        else if(delta == 2) val[2] = val[3] = 1;
        else if(ts[2])      val[3] = 1;
        else                val[2] = 1;
        for(ri i = 4; i < n; i++){
            if(val[i]) continue;
            if(ts[i-1] - (val[i-2] + 1) * (val[i-3] + 1)) val[i] = 1;
            else val[i] = 0;
        }
        val[n] = ts[n-1] / (val[n-2] + 1) - val[n-3] - 1;
        cout << "! ";
        for(ri i = 1; i <= n; i++) cout << val[i] << ' ';
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