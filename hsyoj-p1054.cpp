#include<bits/stdc++.h>
#define File(name) freopen(#name".in", "r", stdin); freopen(#name".out", "w", stdout);
#define ri int
#define Int inline int
#define void inline void
#define Bool inline bool
#define LL inline long long
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 205;
int T, n, m, op, x, y, closedCnt, gameRound, userMap[N][N];
bool gameMap[N][N], gameRunning, userWin;
int mv1[] = {-1,-1,-1, 0, 0, 1, 1, 1};
int mv2[] = {-1, 0, 1,-1, 1,-1, 0, 1};
struct change{
	int x, y, val;
	change() {}
	change(int x, int y, int val): x(x), y(y), val(val) {}
	bool operator < (const change &b) const {
		return x == b.x ? y < b.y : x < b.x;
	}
};
vector<change> modified;
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
bool readmp(){
	char ch = getchar();
	while(ch != '_' && ch != '*') ch = getchar();
	return ch == '*';
}
char translate(int x){
	if(x >= 0) return x + '0';
	if(x == -1) return '_';
	if(x == -2) return 'P';
	if(x == -3) return '?';
}
#define waitOpen(x, y) (userMap[x][y] == -1 || userMap[x][y] == -3)
void open(int x, int y){
	if(gameMap[x][y]){
		gameRunning = false;
		userWin = false; // game lost
		#ifdef DEBUG
		cerr << "Game Lost at <" << x << ' ' << y << ">.\n";
		#endif
		return;
	}
	closedCnt--;
	int cnt = 0;
	for(ri i = 0; i < 8; i++){
		int nx = x + mv1[i], ny = y + mv2[i];
		if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
		if(gameMap[nx][ny]) cnt++;
	}
	userMap[x][y] = cnt;
	modified.push_back(change(x, y, cnt));
	if(cnt == 0){
		for(ri i = 0; i < 8; i++){
			int nx = x + mv1[i], ny = y + mv2[i];
			if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
			if(gameRunning && waitOpen(nx, ny)) open(nx, ny);
		}
	}
}
void checkWin(){
	if(!gameRunning) return;
	if(closedCnt == 0){
		#ifdef DEBUG
		cerr << "Win.\n";
		#endif
		gameRunning = false;
		userWin = true;
	}
	return;
}
void output(){
	sort(modified.begin(), modified.end());
	printf("RUNNING: [");
	for(ri i = 0; i < modified.size(); i++){
		if(i != 0) printf(", ");
		printf("<%d, %d, %c>", modified[i].x, modified[i].y, translate(modified[i].val));
	}
	printf("]\n");
}
int main(){
	#ifdef DEBUG
	File(minesweeper)
	#endif
	T = read<int>();
	#ifdef DEBUG
	cerr << "[Debug Info]\nTotal " << T << " games.\n\n";
	#endif
	while(T--){
		// input & init 
		// < userMap >
		// 0-8  opened
		// -1   closed
		// -2   flag
		// -3   unknown
		n = read<int>(), m = read<int>();
		closedCnt = 0;
		for(ri i = 1; i <= n; i++){
			for(ri j = 1; j <= m; j++){
				gameMap[i][j] = readmp();
				if(!gameMap[i][j]) closedCnt++;
				userMap[i][j] = -1;
			}
		}
		gameRunning = true;
		#ifdef DEBUG
		cerr << "==================== Game " << ++gameRound << " ====================\n"; 
		cerr << "Game started with " << closedCnt << ".\n";
		#endif
		// ope1ration
		while(true){
			op = read<int>();
			if(op == 0) break; // quit
			x = read<int>(), y = read<int>();
			if(!gameRunning){
				puts("INVALID");
				continue;
			}
			modified.clear();
			if(op == 1){
				// left key
				if(waitOpen(x, y)) open(x, y);
				if(gameRunning) output();
				checkWin();
				if(!gameRunning){
					// gameover
					puts(userWin ? "WIN" : "LOSE");
				}
			}
			else if(op == 2){
				// right key
				if(userMap[x][y] < 0){
					userMap[x][y]--;
					if(userMap[x][y] == -4) userMap[x][y] = -1; 
					printf("RUNNING: [<%d, %d, %c>]\n", x, y, translate(userMap[x][y]));
				}
				else output();
			}
			else{
				// mid key
				if(userMap[x][y] < 0){
					output();
					continue;
				}
				int flagCnt = 0;
				for(ri i = 0; i < 8; i++){
					int nx = x + mv1[i], ny = y + mv2[i];
					if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
					flagCnt += userMap[nx][ny] == -2;
				}
				if(flagCnt != userMap[x][y]){
					output();
					continue;
				}
				for(ri i = 0; i < 8; i++){
					int nx = x + mv1[i], ny = y + mv2[i];
					if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
					if(gameRunning && waitOpen(nx, ny)) open(nx, ny);
				}
				if(gameRunning) output();
				checkWin();
				if(!gameRunning){
					// gameover
					puts(userWin ? "WIN" : "LOSE");
				}
			}
			#ifdef DEBUG 
			cerr << "Operation ended with " << closedCnt << ".\n";
			#endif
		}
		#ifdef DEBUG
		cerr << "Gameover.\n\n";
		#endif
		if(gameRunning) puts("QUIT");
		if(T != 0) puts("==========");
	}
	return 0;
}