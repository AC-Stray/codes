#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define int long long
using namespace std;
using ll = long long;
using ull = unsigned long long;
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
namespace Main{
    const int N = 300005;
    int n, m, a[N], b[N], r[N], c;
    bool check(ll mid){
        c = 0;
        for(int i = 0; i < n; i++){
            if(a[i] <= b[i]){
                r[i] = mid, c += m;
                continue;
            }
            int stu = min(m, (mid - 1) / a[i] + 1);
            r[i] = max(0ll, mid - stu * a[i]);
            c += m - stu;
        }
        // for(int i = 0; i < n; i++) cerr << r[i] << " \n"[i == n - 1];
        // cerr << c << endl;
        for(int i = 0; i < n; i++){
            if(r[i] == 0) continue;
            int stu = (r[i] - 1) / b[i] + 1;
            if(c < stu) return false;
            c -= stu;
        }
        return true;
    }
    void Main(){
        input(n, m);
        for(int i = 0; i < n; i++) input(a[i]);
        for(int i = 0; i < n; i++) input(b[i]);
        ll l = 0, r = 2e18, ans = 0;
        while(l <= r){
            ll mid = l + r >> 1;
            if(check(mid)) l = mid + 1, ans = mid;
            else r = mid - 1;
        }
        write(ans);
        return;
    }
}
signed main(){
    #ifdef Liuxizai
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    #endif
    Main::Main();
    return 0;
}