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
    const int N = 100005;
    int t, n;
    string s, rs;
    bool ans;
    map<string, bool> mp, mp2;
    void Main(){
        input(t);
        while(t--){
            input(n);
            ans = false, mp.clear(), mp2.clear();
            for(int i = 0; i < n; i++){
                cin >> s;
                if(ans) continue;
                rs = s; reverse(rs.begin(), rs.end());
                if(s.size() == 1) ans = true;
                else if(s.size() == 2){
                    mp[s] = true;
                    if(mp[rs] || mp2[rs]) ans = true;
                }
                else{
                    mp[s] = true;
                    if(mp[rs] || mp[rs.substr(0, 2)]) ans = true;
                    mp2[s.substr(0, 2)] = true;
                }
            }
            puts(ans ? "YES" : "NO");
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