#include<bits/stdc++.h>
#define int long long
using namespace std;

int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int y, m, d, t;
int q, r;

inline int readint(){
    int f = 1, n = 0;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f *= -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        n = n * 10 + (ch - '0');
        ch = getchar();
    }
    return f * n;
}

inline bool isrunnian(int n){
    if(n >= 1582)
        return n % 400 == 0 || n % 4 == 0 && n % 100 != 0;
    if(n < 0){
        n++;
        return n % 4 == 0;
    }
    return n % 4 == 0;
}
inline int get1000000(int y){
    if(y == -4713) return 365242538;
    return 365242500;
}
inline int get10000(int y){
    if(y == -4713) return 3652463;
    return 3652425;
}
inline int get100(int y){
    if(y < 1488) return 36525;
    if(y == 1488) return 36515;
    if((y - 88) % 400 == 300) return 36525;
    return 36524;
}
inline int get1(int y){
    if(y == 1582) return 355;
    if(isrunnian(y)) return 366;
    return 365;
}
inline int getday(int y, int m){
    if(y == 1582 && m == 10) return 21;
    if(isrunnian(y) && m == 2) return 29;
    return days[m];
}

signed main(){
    // freopen("in", "r", stdin);
    // freopen("out", "w", stdout);
    // y = 1000;
    // int sum = 0;
    // for(int i = 0; i < 100; i++){
    //     sum += get10000(y);
    //     if(y == -4713) y = 5288;
    //     else y += 10000;
    // }
    // printf("%lld", sum);
    q = readint();
    while(q--){
        r = readint();
        y = -4713, m = 1, d = 1;
        while((t = get1000000(y)) <= r){
            r -= t;
            if(y == -4713) y = 995288;
            else y += 1000000;
        }
        while((t = get10000(y)) <= r){
            r -= t;
            if(y == -4713) y = 5288;
            else y += 10000;
        }
        while((t = get100(y)) <= r){
            r -= t;
            if(y == -13) y = 88;
            else y += 100;
        }
        while((t = get1(y)) <= r){
            r -= t;
            y++;
            if(y == 0) y++;
        }
        while((t = getday(y, m)) <= r){
            r -= t;
            m++;
        }
        d += r;
        if(m == 10 && y == 1582) d += 10;
        printf("%lld %lld %lld ", d, m, abs(y));
        if(y < 0) printf("BC");
        printf("\n");
    }
    return 0;
}