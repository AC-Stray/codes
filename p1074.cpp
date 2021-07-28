#include<bits/stdc++.h>
#define File(name) freopen(name".in", "r", stdin); freopen(name".out", "w", stdout);
#define Int inline int
#define Void inline void
#define Bool inline bool
#define DB inline double
#define LL inline long long
#define ri register int
#define re register
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
struct node{
    int id, zeroCnt;
    Bool operator < (const node &b) const{
        return zeroCnt < b.zeroCnt;
    }
}line[9];
int start, ans, sudoku[9][9];
int score[9][9] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 9,10, 9, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6}
};
bool row[9][10], column[9][10], cell[9][10];
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
Int getCell(int x, int y){
    if(x < 3 && y < 3) return 0;
    else if(x < 6 && y < 3) return 1;
    else if(y < 3) return 2;
    else if(x < 3 && y < 6) return 3;
    else if(x < 6 && y < 6) return 4;
    else if(y < 6) return 5;
    else if(x < 3) return 6;
    else if(x < 6) return 7;
    else return 8;
}
Void dfs(int now, int nowScore){
    if(now == 9){
        if(nowScore > ans){
            ans = nowScore;
            // cout << "\n\n";
            // for(ri i = 0; i < 9; i++){
            //     for(ri j = 0; j < 9; j++) cout << sudoku[i][j] << ' ';
            //     cout << endl;
            // }
            // cout << ans;
            // cout << "\n\n";
        }
        return;
    }
    int y = line[now].id;
    bool flag = false;
    for(ri i = 0; i < 9; i++){
        if(sudoku[y][i] != 0) continue;
        flag = true;
        for(ri j = 1; j <= 9; j++){
            if(row[y][j] || column[i][j] || cell[getCell(y, i)][j]) continue;
            row[y][j] = column[i][j] = cell[getCell(y, i)][j] = true;
            sudoku[y][i] = j;
            dfs(now, nowScore + j * score[y][i]);
            sudoku[y][i] = 0;
            row[y][j] = column[i][j] = cell[getCell(y, i)][j] = false;
        }
        break;
    }
    if(!flag) dfs(now+1, nowScore);
}
int main(){
    for(ri i = 0; i < 9; i++){
        line[i].id = i;
        for(ri j = 0; j < 9; j++){
            input(sudoku[i][j]);
            if(sudoku[i][j] == 0) line[i].zeroCnt++;
            else{
                row[i][sudoku[i][j]] = true;
                column[j][sudoku[i][j]] = true;
                cell[getCell(i, j)][sudoku[i][j]] = true;
                start += sudoku[i][j] * score[i][j];
            }
        }
    }
    sort(line, line+9);
    ans = -1;
    dfs(0, start);
    cout << ans;
	return 0;
}