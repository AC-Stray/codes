#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
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
    const int N = 505;
    int n, m, s[N];
    pair<int, int> a[N];
    double f[N][N], ans;
    void Main(){
        input(n, m);
        for(int i = 1; i <= n; i++){
            input(a[i].second, a[i].first);
            if(a[i].first == -1) a[i].first = 1e9;
        }
        sort(a + 1, a + n + 1);
        for(int i = 1; i <= n; i++) s[i] = s[i-1] + a[i].second;
        for(int i = 0; i <= n; i++) for(int j = 0; j <= n; j++) f[i][j] = 1e9;
        f[0][0] = 0;
        for(int i = 1; i <= m; i++){
            for(int j = 1; j <= i; j++){

            }
        }
        vector<int> tmp;
        for(int i = 1; i <= n; i++) tmp.push_back(a[i].second);
        sort(tmp.begin(), tmp.end());
        for(int i = 0; i < m; i++) ans += tmp[i];
        for(int i = 1; i <= m; i++){
            double tans = 1e9, sum = 0;
            int best;
            tmp.erase(lower_bound(tmp.begin(), tmp.end(), a[i].second));
            for(int j = 0; j < m - i; j++) sum += tmp[j];
            for(int j = 1; j <= i; j++){
                double calc = f[i][j] + sum / (j + 1);
                if(calc < tans){
                    tans = calc;
                    best = j;
                }
            }
            ans = min(ans, tans);
            fprintf(stderr, "%d %d: %.15lf\n", i, best, tans);
        }
        printf("%.15lf", ans);
        return;
    }
}
int main(){
    #ifdef Liuxizai
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    #endif
    Main::Main();
    return 0;
}