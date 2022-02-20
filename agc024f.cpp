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
    const int N = 21;
    int n, k, ansl, ans, f[N][1<<N];
    int getdigit(){
        char ch = getchar();
        while(!isdigit(ch)) ch = getchar();
        return ch - '0';
    }
    Int fbit(int x) { return 31 - __builtin_clz(x); }
    void print(string s, int i, int j){
        cout << s;
        int len = __lg(j), t = j - (1 << len);
        int x = t >> (len - i), y = t & ((1 << len - i) - 1);
        for(int k = i - 1; k >= 0; k--) putchar('0' + (x >> k & 1));
        cout << " | ";
        for(int k = len - i - 1; k >= 0; k--) putchar('0' + (y >> k & 1));
        puts("");
    }
    void Main(){
        input(n, k);
        for(int i = 0; i <= n; i++) for(int j = 0; j < (1 << i); j++){
        	f[0][j+(1<<i)] = getdigit();
         	// print("in:   ", 0, j + (1 << i));
		}
        for(int i = 0; i <= n; i++){
            for(int j = (1 << i + 1); j < (1 << n + 1); j++){
                // print("ori:  ", i, j);
                int len = __lg(j), t = j - (1 << len);
                int x = t >> (len - i), y = t & ((1 << len - i) - 1);
                f[i][x+(1<<i)] += f[i][j];
                if(y){
                    int len0 = fbit(y);
                    int y0 = y & ((1 << len0) - 1);
                    f[i+1][(1<<len0+i+1)+(x<<len0+1)+(1<<len0)+y0] += f[i][j];
                    // print("one:  ", i+1, (1<<len0+i+1)+(x<<len0+1)+(1<<len0)+y0);
                }
                if((1 << len - i) - 1 - y){
                    int len0 = fbit((1 << len - i) - 1 - y);
                    int y0 = y & ((1 << len0) - 1);
                    f[i+1][(1<<len0+i+1)+(x<<len0+1)+y0] += f[i][j];
                    // print("zero: ", i+1, (1<<len0+i+1)+(x<<len0+1)+y0);
                }
            }
        }
        for(int i = 1; i < (1 << n + 1); i++){
       	    // cout << f[__lg(i)][i];
       	    // print("test: ", __lg(i), i);
            if(f[__lg(i)][i] >= k){
                if(ansl < __lg(i)){
                    ansl = __lg(i);
                    ans = i - (1 << __lg(i) + 1);
                }
            }
        }
        for(int i = ansl - 1; i >= 0; i--) putchar('0' + (ans >> i & 1));
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
