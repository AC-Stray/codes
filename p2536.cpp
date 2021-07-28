#include<bits/stdc++.h>
#define ri register int
using namespace std;
const int N = 1005;
int cnt, n, len1, len2;
bool f[N][N];
char s[N], t[N];
int main(){
    scanf("%s", s + 1);
    len1 = strlen(s + 1);
    s[0] ='*';
    scanf("%d", &n);
    for(ri k = 0; k < n; k++){
        scanf("%s", t + 1);
        len2 = strlen(t + 1);
        memset(f, 0, sizeof(f));
        for(ri i = 0; s[i] == '*'; i++) f[i][0] = true;
        for(ri i = 1; i <= len1; i++){
            for(ri j = 1; j <= len2; j++){
                if(s[i] == '?') f[i][j] = f[i-1][j-1];
                else if(s[i] == '*') f[i][j] = f[i][j-1] || f[i-1][j-1] || f[i-1][j];
                else f[i][j] = f[i-1][j-1] && s[i] == t[j];
            }
        }
        if(!f[len1][len2]) cnt++;
    }
    printf("%d", cnt);
    return 0;
}
