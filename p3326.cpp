#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
const int ansSIZE = 5000;
char cube[25][25] = {
    "    +-------+",
    "   /a\\cccc'/|",
    "  /aa.*'dd/e|",
    " /.bbbb\\d/e/|",
    "+-------+e.f|",
    "|\\iiiii/|\\:f|",
    "|k\\iii/j|g*f|",
    "|kk\\i/jj|g:\\|",
    "|kkkXjjj|g'h+",
    "|kk/l\\jj|/h/",
    "|k/lll\\j|h/",
    "|/lllll\\|/",
    "+-------+"
};
char ch, ans[ansSIZE+5][ansSIZE+5];
int size1 = 0x7fffffff, size2;
int m, n, mh, cnt, h[105][105], exist[105][105][205], color[1000005][15];
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
int toint(char ch){
    switch(ch){
        case 'R': return 1;
        case 'G': return 2;
        case 'B': return 4;
    }
    return 0;
}
char tochar(int id){
    switch(id){
        case 0: /* 000 */ return 'K';
        case 1: /* 001 */ return 'R';
        case 2: /* 010 */ return 'G';
        case 3: /* 011 */ return 'Y';
        case 4: /* 100 */ return 'B';
        case 5: /* 101 */ return 'P';
        case 6: /* 110 */ return 'C';
        case 7: /* 111 */ return 'W';
    }
    return '?'; 
}
#define ncolor color[exist[i][j][k]]
void solve(int d, int c){
    if(d == 0){
        for(ri i = 1; i <= n; i++){
            for(ri j = 1; j <= m; j++){
                for(ri k = 1; k <= h[i][j]; k++){
                    bool back = false;
                    for(ri p = i-1, q = j-1, r = k+1; p >= 0 && q >= 0 && r <= mh; p--, q--, r++) if(exist[p][q][r]) { back = true; break; }
                    if(back) continue;
                    bool flag1 = true, flag2 = true;
                    for(ri p = i-1, q = j-1, r = k+1; p >= 0 && q >= 0 && r <= mh; p--, q--, r++) if(exist[p][q][r]) { flag1 = flag2 = false; break; }
                    for(ri p = i, q = j-1, r = k+1; p >= 0 && q >= 0 && r <= mh && flag1; p--, q--, r++) if(exist[p][q][r]) { flag1 = false; break; }
                    for(ri p = i-1, q = j, r = k+1; p >= 0 && q >= 0 && r <= mh && flag2; p--, q--, r++) if(exist[p][q][r]) { flag2 = false; break; }
                    if(flag1){
                        ncolor[0] |= c;
                        ncolor[1] |= c;
                    }
                    if(flag2){
                        ncolor[2] |= c;
                        ncolor[3] |= c;
                    }
                }
            }
        }
    }
    if(d == 1){
        for(ri i = 1; i <= n; i++){
            for(ri j = 1; j <= m; j++){
                for(ri k = 1; k <= h[i][j]; k++){
                    bool flag1 = true;
                    for(ri p = i-1, q = j, r = k+1; p >= 0 && r <= mh; p--, r++) if(exist[p][q][r]) { flag1 = false; break; }
                    if(flag1){
                        ncolor[0] |= c;
                        ncolor[1] |= c;
                        ncolor[2] |= c;
                        ncolor[3] |= c;
                    }
                }
            }
        }
    }
    if(d == 2){
        for(ri i = 1; i <= n; i++){
            for(ri j = 1; j <= m; j++){
                for(ri k = 1; k <= h[i][j]; k++){
                    bool back = false;
                    for(ri p = i-1, q = j+1, r = k+1; p >= 0 && q <= m && r <= mh; p--, q++, r++) if(exist[p][q][r]) { back = true; break; }
                    if(back) continue;
                    bool flag1 = true, flag2 = true, flag3 = true, flag4 = true;
                    for(ri p = i-1, q = j+1, r = k+1; p >= 0 && q <= m && r <= mh; p--, q++, r++) if(exist[p][q][r]) { flag1 = flag2 = false; break; }
                    for(ri p = i-1, q = j, r = k+1; p >= 0 && q <= m && r <= mh && flag1; p--, q++, r++) if(exist[p][q][r]) { flag1 = false; break; }
                    for(ri p = i, q = j+1, r = k+1; p >= 0 && q <= m && r <= mh && flag2; p--, q++, r++) if(exist[p][q][r]) { flag2 = false; break; }
                    for(ri p = i, q = j+1, r = k; p >= 0 && q <= m && r <= mh; p--, q++, r++) if(exist[p][q][r]) { flag3 = flag4 = false; break; }
                    for(ri p = i-1, q = j+1, r = k; p >= 0 && q <= m && r <= mh && flag4; p--, q++, r++) if(exist[p][q][r]) { flag4 = false; break; }
                    if(flag1){
                        ncolor[0] |= c;
                        ncolor[2] |= c;
                    }
                    if(flag2){
                        ncolor[1] |= c;
                        ncolor[3] |= c;
                    }
                    if(flag3){
                        ncolor[4] |= c;
                        ncolor[6] |= c;
                    }
                    if(flag4){
                        ncolor[5] |= c;
                        ncolor[7] |= c;
                    }
                }
            }
        }
    }
    if(d == 3){
        for(ri i = 1; i <= n; i++){
            for(ri j = 1; j <= m; j++){
                for(ri k = 1; k <= h[i][j]; k++){
                    bool flag1 = true;
                    for(ri p = i, q = j-1, r = k+1; q >= 0 && r <= mh; q--, r++) if(exist[p][q][r]) { flag1 = false; break; }
                    if(flag1){
                        ncolor[0] |= c;
                        ncolor[1] |= c;
                        ncolor[2] |= c;
                        ncolor[3] |= c;
                    }
                }
            }
        }
    }
    if(d == 4){
        for(ri i = 1; i <= n; i++){
            for(ri j = 1; j <= m; j++){
                ri k = h[i][j];
                ncolor[0] |= c;
                ncolor[1] |= c;
                ncolor[2] |= c;
                ncolor[3] |= c;
            }
        }
    }
    if(d == 5){
        for(ri i = 1; i <= n; i++){
            for(ri j = 1; j <= m; j++){
                for(ri k = 1; k <= h[i][j]; k++){
                    bool flag1 = true, flag2 = true;
                    for(ri p = i, q = j+1, r = k+1; q <= m && r <= mh; q++, r++) if(exist[p][q][r]) { flag1 = false; break; }
                    for(ri p = i, q = j+1, r = k; q <= m && r <= mh; q++, r++) if(exist[p][q][r]) { flag2 = false; break; }
                    if(flag1){
                        ncolor[0] |= c;
                        ncolor[1] |= c;
                        ncolor[2] |= c;
                        ncolor[3] |= c;
                    }
                    if(flag2){
                        ncolor[4] |= c;
                        ncolor[5] |= c;
                        ncolor[6] |= c;
                        ncolor[7] |= c;
                    }
                }
            }
        }
    }
    if(d == 6){
        for(ri i = 1; i <= n; i++){
            for(ri j = 1; j <= m; j++){
                for(ri k = 1; k <= h[i][j]; k++){
                    bool back = false;
                    for(ri p = i+1, q = j-1, r = k+1; p <= n && q >= 0 && r <= mh; p++, q--, r++) if(exist[p][q][r]) { back = true; break; }
                    if(back) continue;
                    bool flag1 = true, flag2 = true, flag3 = true, flag4 = true;
                    for(ri p = i+1, q = j-1, r = k+1; p <= n && q >= 0 && r <= mh; p++, q--, r++) if(exist[p][q][r]) { flag1 = flag2 = false; break; }
                    for(ri p = i, q = j-1, r = k+1; p <= n && q >= 0 && r <= mh && flag1; p++, q--, r++) if(exist[p][q][r]) { flag1 = false; break; }
                    for(ri p = i+1, q = j, r = k+1; p <= n && q >= 0 && r <= mh && flag2; p++, q--, r++) if(exist[p][q][r]) { flag2 = false; break; }
                    for(ri p = i+1, q = j, r = k; p <= n && q >= 0 && r <= mh; p++, q--, r++) if(exist[p][q][r]) { flag3 = flag4 = false; break; }
                    for(ri p = i+1, q = j-1, r = k; p <= n && q >= 0 && r <= mh && flag4; p++, q--, r++) if(exist[p][q][r]) { flag4 = false; break; }
                    if(flag1){
                        ncolor[0] |= c;
                        ncolor[2] |= c;
                    }
                    if(flag2){
                        ncolor[1] |= c;
                        ncolor[3] |= c;
                    }
                    if(flag3){
                        ncolor[8] |= c;
                        ncolor[9] |= c;
                    }
                    if(flag4){
                        ncolor[10] |= c;
                        ncolor[11] |= c;
                    }
                }
            }
        }
    }
    if(d == 7){
        for(ri i = 1; i <= n; i++){
            for(ri j = 1; j <= m; j++){
                for(ri k = 1; k <= h[i][j]; k++){
                    bool flag1 = true, flag2 = true;
                    for(ri p = i+1, q = j, r = k+1; p <= n && r <= mh; p++, r++) if(exist[p][q][r]) { flag1 = false; break; }
                    for(ri p = i+1, q = j, r = k; p <= n && r <= mh; p++, r++) if(exist[p][q][r]) { flag2 = false; break; }
                    if(flag1){
                        ncolor[0] |= c;
                        ncolor[1] |= c;
                        ncolor[2] |= c;
                        ncolor[3] |= c;
                    }
                    if(flag2){
                        ncolor[8] |= c;
                        ncolor[9] |= c;
                        ncolor[10] |= c;
                        ncolor[11] |= c;
                    }
                }
            }
        }
    }
    if(d == 8){
        for(ri i = 1; i <= n; i++){
            for(ri j = 1; j <= m; j++){
                for(ri k = 1; k <= h[i][j]; k++){
                    bool back = false;
                    for(ri p = i+1, q = j+1, r = k+1; p <= n && q <= m && r <= mh; p++, q++, r++) if(exist[p][q][r]) { back = true; break; }
                    if(back) continue;
                    bool flag1 = true, flag2 = true, flag3 = true, flag4 = true, flag5 = true, flag6 = true;
                    for(ri p = i+1, q = j+1, r = k+1; p <= n && q <= m && r <= mh; p++, q++, r++) if(exist[p][q][r]) { flag1 = flag2 = false; break; }
                    for(ri p = i, q = j+1, r = k+1; p <= n && q <= m && r <= mh && flag1; p++, q++, r++) if(exist[p][q][r]) { flag1 = false; break; }
                    for(ri p = i+1, q = j, r = k+1; p <= n && q <= m && r <= mh && flag2; p++, q++, r++) if(exist[p][q][r]) { flag2 = false; break; }
                    for(ri p = i, q = j+1, r = k; p <= n && q <= m && r <= mh; p++, q++, r++) if(exist[p][q][r]) { flag3 = flag4 = false; break; }
                    for(ri p = i+1, q = j, r = k; p <= n && q <= m && r <= mh; p++, q++, r++) if(exist[p][q][r]) { flag5 = flag6 = false; break; }
                    for(ri p = i+1, q = j+1, r = k; p <= n && q <= m && r <= mh && (flag3 || flag5); p++, q++, r++) if(exist[p][q][r]) { flag3 = flag5 = false; break; }
                    if(flag1){
                        ncolor[2] |= c;
                        ncolor[3] |= c;
                    }
                    if(flag2){
                        ncolor[0] |= c;
                        ncolor[1] |= c;
                    }
                    if(flag3){
                        ncolor[6] |= c;
                        ncolor[7] |= c;
                    }
                    if(flag4){
                        ncolor[4] |= c;
                        ncolor[5] |= c;
                    }
                    if(flag5){
                        ncolor[9] |= c;
                        ncolor[11] |= c;
                    }
                    if(flag6){
                        ncolor[8] |= c;
                        ncolor[10] |= c;
                    }
                }
            }
        }
    }
}
#undef ncolor
void creat(int x, int y, int id){
    for(ri i = 0; i < 13; i++){
        for(ri j = 0; j < 13; j++){
            if(cube[i][j] == ' ' || cube[i][j] == '\0') continue;
            ans[x-12+i][y+j] = cube[i][j];
            if(ans[x-12+i][y+j] >= 'a' && ans[x-12+i][y+j] <= 'l') ans[x-12+i][y+j] = tochar(color[id][ans[x-12+i][y+j]-'a']);
            size1 = min(size1, x-12+i);
            size2 = max(size2, y+j);
        }
    }
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("ans1.out", "w", stdout);
#endif
    input(n, m);
    for(ri i = 1; i <= n; i++){
        for(ri j = 1; j <= m; j++){
            input(h[i][j]);
            mh = max(mh, h[i][j]);
            for(ri k = 1; k <= h[i][j]; k++){
                exist[i][j][k] = ++cnt;
            }
        }
    }
    for(ri i = 0; i < 3; i++){
        for(ri j = 0; j < 3; j++){
            cin >> ch;
            if(ch == '*') continue;
            solve(i*3+j, toint(ch));
        }
    }
    for(ri i = 1; i <= n; i++){
        for(ri j = 1; j <= m; j++){
            for(ri k = 1; k <= h[i][j]; k++){
                creat(ansSIZE-(n-i)*4-(k-1)*8, (n-i)*4+(j-1)*8, exist[i][j][k]);
            }
        }
    }
    for(ri i = size1; i <= ansSIZE; i++){
        for(ri j = 0; j <= size2; j++){
            if(ans[i][j] == '\0') putchar(' ');
            else putchar(ans[i][j]);
        }
        puts("");
    }
    return 0;
}
