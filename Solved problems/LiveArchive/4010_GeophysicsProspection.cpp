#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
#define invrep(i,a,b) for(int i=a; i>=b; i--)
typedef tuple<int,int,int> iii;

const int MAXP = 50;
const int MAXK = 50;
const int MAXM = 50;
int p, k, m;
char board[MAXM][MAXP][MAXK+1];
int dirs[6][3] = {
	{1, 0, 0},
	{-1, 0, 0},
	{0, 1, 0},
	{0, -1, 0},
	{0, 0, 1},
	{0, 0, -1}
};

int bfs(int x, int y, int z) {
	char c = board[x][y][z];
	queue<iii> q;
	q.push(iii(x,y,z));
	board[x][y][z] = '*';
	int count = 1;
	while (!q.empty()) {
		tie(x,y,z) = q.front(); q.pop();
		rep(i,0,5) {
			int xx = x + dirs[i][0], yy = y + dirs[i][1], zz = z + dirs[i][2];
			if (0 <= xx && xx < m && 0 <= yy && yy < p && 0 <= zz && zz < k
				&& board[xx][yy][zz] == c) {
				count++;
				board[xx][yy][zz] = '*';
				q.push(iii(xx,yy,zz));
			} 
		}
	}
	return count;
}

int main() {
	int case_ = 1;
	while (scanf("%d%d%d",&p,&k,&m)==3) {
		rep(i,0,m-1) rep(j,0,p-1) scanf("%s", board[i][j]);
		vector<int> counts[4];
		rep(x,0,m-1) rep(y,0,p-1) rep(z,0,k-1) {
			char c = board[x][y][z];
			if (c != '*') counts[c - 'a'].push_back(bfs(x,y,z));
		}
		if (case_ > 1) puts("");
		printf("Case %d:\n", case_);
		rep(i,0,3) {
			printf("%c",(char)(i + 'a'));
			if (counts[i].size() == 0) puts(" 0");
			else {
				sort(counts[i].begin(), counts[i].end());
				invrep(j, counts[i].size()-1, 0) printf(" %d", counts[i][j]);
				puts("");
			}
		}
		case_++;
	}
	return 0;
}