#include<bits/stdc++.h>
#define ri register int
using namespace std;
const int N = 1000005;
int len1, len2, nxt[N];
char s1[N], s2[N];
int main(){
	scanf("%s%s", s1+1, s2+1);
	len1 = strlen(s1+1), len2 = strlen(s2+1);
	for(ri i = 2, j = 0; i <= len2; i++){
		while(j && s2[i] != s2[j+1]) j = nxt[j];
		if(s2[i] == s2[j+1]) j++;
		nxt[i] = j;
	}
	for(ri i = 1, j = 0; i <= len1; i++){
		while(j && s1[i] != s2[j+1]) j = nxt[j];
		if(s1[i] == s2[j+1]) j++;
		if(j == len2) cout << i - len2 + 1 << endl, j = nxt[j];
	}
	for(ri i = 1; i <= len2; i++) cout << nxt[i] << ' ';
}
