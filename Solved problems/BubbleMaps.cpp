#include <cstdio>
#include <cstring>
using namespace std;

#define up 0
#define right 1
#define down 2
#define left 3

char buff1[5001];
char buff2[5001];
char bannedLetters[4][2] = { { 'p', 'q' }, { 'q', 'r' }, { 'r', 's' }, { 's',
		'p' } };
char adjLetter[4][4] = { { 's', 'r', 'q', 'p' }, { 'q', 'p', 's', 'r' }, { 's',
		'r', 'q', 'p' }, { 'q', 'p', 's', 'r' } };
bool shareSquare[4][4] = { { false, false, true, true }, { true, false, false,
		true }, { true, true, false, false }, { false, true, true, false } };

int dirs[4] = { up, down, left, right };

int main() {
	int N;
	scanf("%d", &N);
	while (N-- > 0) {
		scanf("%s", buff1);
		int length = strlen(buff1);
		//-----
		int letterCounts[4] = { 0 };
		for (int i = 0; i < length; ++i)
			letterCounts[buff1[i] - 'p']++;
		//-----
		for (int i = 0; i < 4; ++i) {
			int dir = dirs[i];
			int bl1 = bannedLetters[dir][0] - 'p';
			int bl2 = bannedLetters[dir][1] - 'p';
			if (letterCounts[bl1] + letterCounts[bl2] == length - 1) {
				printf("<none>");
			} else {
				for (int j = length - 1; j > 0; --j) {
					char c = buff1[j];
					int adj_c = adjLetter[dir][c - 'p'];
					buff2[j] = adj_c;
					if (shareSquare[dir][c - 'p']) {
						for (int k = j - 1; k > 0; --k)
							buff2[k] = buff1[k];
						break;
					}
				}
				buff2[0] = 'm';
				printf("%.*s", length, buff2);
			}
			if (i < 3)
				printf(" ");
		}
		printf("\n");

	}
	return 0;
}
