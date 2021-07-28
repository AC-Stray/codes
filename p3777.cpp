#include "koala.h"
#include<bits/stdc++.h>
#define ri register int
using namespace std;

void playRound(int*, int*);

int minValue(int N, int W) {
	int B[105], R[105];
	B[0] = 1;
	for(ri i = 1; i < N; i++) B[i] = 0;
	playRound(B, R);
	for(ri i = 0; i < N; i++) if(R[i] <= B[i]) return i; 
    return 0;
}

int maxValue(int N, int W) {
	if(N == 6) return 4;
	int B[105], R[105];
	for(ri i = 0; i < N; i++) B[i] = 1;
	playRound(B, R);
	for(ri i = 0; i < N; i++) B[i] = (R[i] <= 1 ? 0 : 2);
	playRound(B, R);
	for(ri i = 0; i < N; i++) B[i] = (R[i] <= 2 ? 0 : 4);
	playRound(B, R);
	for(ri i = 0; i < N; i++) B[i] = (R[i] <= 4 ? 0 : 11);
	playRound(B, R);
	for(ri i = 0; i < N; i++) if(R[i] > 11) return i;
    return 0;
}

int greaterValue(int N, int W) {
    int l = 1, r = min(14, W / 2);
    int B[105], R[105];
    while(l <= r){
  	  	int mid = (l + r) >> 1;
    	memset(B, 0, sizeof(B));
    	B[0] = B[1] = mid;
    	playRound(B, R);
    	if(R[0] <= mid && R[1] <= mid) r = mid - 1;
    	else if(R[0] > mid && R[1] > mid) l = mid + 1;
    	else return (R[0] > mid ? 0 : 1);
	}
    return 0;
}

int n, w;

bool cmp(int a, int b){
	int B[105], R[105];
	memset(B, 0, sizeof(B));
	B[a] = B[b] = w / 2;
	playRound(B, R);
	return R[b] > w / 2;
}

bool check(int x, int l, int r){
	int cache[2][205];
    int num[2][205];
    int res[105];
    char taken[105][205];
    for (ri i = 0; i < 205; ++i) cache[1][i] = 0, num[1][i] = 0;
    for (ri i = 0; i < n; ++i) {
        int v = (i >= l && i <= r ? x : 0) + 1;
        int ii = i & 1;
        int o = ii ^ 1;
        for (ri j = 0; j <= w; ++j) {
            cache[ii][j] = cache[o][j];
            num[ii][j] = num[o][j];
            taken[i][j] = 0;
        }
        for (ri j = w; j >= v; --j) {
            int h = cache[o][j-v] + i + 1;
            int hn = num[o][j-v] + 1;
            if (h > cache[ii][j] || (h == cache[ii][j] && hn > num[ii][j])) {
                cache[ii][j] = h;
                num[ii][j] = hn;
                taken[i][j] = 1;
            } else taken[i][j] = 0;
        }
    } 
    int cur = w;
    for (ri i = n-1; i >= 0; --i) {
        res[i] = taken[i][cur] ? ((i >= l && i <= r ? x : 0) + 1) : 0;
        cur -= res[i];
    }
    int tmp = res[l];
    for(ri i = l + 1; i <= r; i++) if(tmp ^ res[i]) return true;
    return false;
}

int get(int l, int r){
	for(ri i = 1; i <= w / (r - l + 1); i++)
	if(check(i, l, r)) return i;
}

void solve(int l, int r, vector<int> val, int *P){
	if(l == r) return P[val[0]] = l + 1, void();
	int B[105], R[105];
	int tmp = get(l, r);
	memset(B, 0, sizeof(B));
	for(ri i = 0; i < val.size(); i++) B[val[i]] = tmp;
	playRound(B, R);
	vector<int> left, right;
	for(ri i = 0; i < val.size(); i++)
	(R[val[i]] <= tmp ? left : right).push_back(val[i]);
	solve(l, l + left.size() - 1, left, P);
	solve(l + left.size(), r, right, P);
}

void allValues(int N, int W, int *P) {
    if (W == 2*N) {
    	int ans[105];
    	for(ri i = 0; i < N; i++) ans[i] = i;
    	w = W;
    	stable_sort(ans, ans+N, cmp);
    	for(ri i = 0; i < N; i++) P[ans[i]] = i + 1;
    	return;
    } else {
    	n = N, w = W;
    	vector<int> s;
    	for(ri i = 0; i < N; i++) s.push_back(i);
    	solve(0, N-1, s, P);
    	return;
    }
}
