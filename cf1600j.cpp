#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri register int
#define Int inline int
#define Void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
const int MOD = 998244353;
const int inf = 0x3f3f3f3f;
const int N = 1005;
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
    int n, m, p, fa[N*N], cnt[N*N];
    int mv1[] = {1, 0};
    int mv2[] = {0, 1};
    Int id(int x, int y) { return x * m + y; }
    int get(int x){
        if(fa[x] == x) return x;
        return fa[x] = get(fa[x]);
    }
    void unite(int x, int y){
        fa[get(x)] = get(y);
    }
    void Main(){
        input(n, m);
        for(ri i = 0; i < n * m; i++) fa[i] = i;
        for(ri i = 0; i < n; i++){
            for(ri j = 0; j < m; j++){
                input(p);
                p >>= 1;
                for(ri k = 0; k < 2; p >>= 1, k++){
                    if(p&1) continue;
                    int nx = i + mv1[k], ny = j + mv2[k];
                    unite(id(i, j), id(nx, ny));
                }
            }
        }
        for(ri i = 0; i < n * m; i++) cnt[get(i)]++;
        #ifdef Liuxizai
        for(ri i = 0; i < n; i++){
            for(ri j = 0; j < m; j++) cerr << get(id(i, j)) << ' ';
            cerr << endl;
        }
        #endif
        sort(cnt, cnt + n * m, greater<int>());
        for(ri i = 0; i < n * m; i++){
            if(cnt[i] == 0) break;
            write(cnt[i]), putchar(' ');
        }
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