#include<bits/stdc++.h>
#define ri register long long
using namespace std;
typedef long long ll;
extern "C"{
    void MinMax(ll, ll, ll*, ll*);
    ll findGap(int T, int N){
        ll ans = 0;
        if(T == 1){
            ll a[100005];
            a[0] = 0, a[N+1] = 0x7fffffffffffffff;
            for(ri i = 1, j = N; i <= j; i++, j--){
                MinMax(a[i-1]+1, a[j+1]-1, &a[i], &a[j]);
            }
            for(ri i = 2; i <= N; i++) ans = max(ans, a[i]-a[i-1]);
        }
        else{
            ll len, mn, mx, l, r, lst = 0;
            MinMax(0, 1e18, &mn, &mx);
            len = (mx - mn + N - 2) / (N - 1);
            lst = mn;
            for(ri i = mn; i + 1 < mx; i += len){
                MinMax(i+1, min(mx-1, i+len), &l, &r);
                ans = max(ans, l - lst);
                if(r != -1) lst = r;
            }
            ans = max(ans, mx - lst);
        }
        return ans;
    }
}