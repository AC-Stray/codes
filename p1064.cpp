#include<bits/stdc++.h>
//#define DEBUG
using namespace std;
struct object{
    int v, w;
    object(int vv = 0, int ww = 0): v(vv), w(ww) {}
};
object mainObject[32005], annexObject[32005][2];
int n, m, v, p, q, dp[32005];
int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++){
        cin >> v >> p >> q;
        if(q == 0) mainObject[i] = object(v, v*p);
        else if(annexObject[q][0].w == 0) annexObject[q][0] = object(v, v*p);
        else annexObject[q][1] = object(v, v*p);
    }
    for(int i = 1; i <= m; i++) for(int j = n; mainObject[i].w != 0 && j >= mainObject[i].v; j--){
        dp[j] = max(dp[j], dp[j-mainObject[i].v]+mainObject[i].w);
        
        if(j >= mainObject[i].v + annexObject[i][0].v)
            dp[j] = max(dp[j], dp[j-mainObject[i].v-annexObject[i][0].v]+mainObject[i].w+annexObject[i][0].w);
        
        if(j >= mainObject[i].v + annexObject[i][1].v)
            dp[j] = max(dp[j], dp[j-mainObject[i].v-annexObject[i][1].v]+mainObject[i].w+annexObject[i][1].w);
        
        if(j >= mainObject[i].v + annexObject[i][0].v + annexObject[i][1].v)
            dp[j] = max(dp[j], dp[j-mainObject[i].v-annexObject[i][0].v-annexObject[i][1].v]+mainObject[i].w+annexObject[i][0].w+annexObject[i][1].w);
    }
    #ifndef DEBUG
    cout << dp[n];
    #else
    for(int i = 0; i <= n; i++) cout << dp[i] << " ";
    #endif
    return 0;
}