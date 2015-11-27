#include <cstdio>
#include <cstring>
using namespace std;

char buff[500];

char brailleDigits[10][7] = {
//
		".***..",//0
		"*.....", //1
		"*.*...", //2
		"**....", //3
		"**.*..", //4
		"*..*..", //5
		"***...", //6
		"****..", //7
		"*.**..", //8
		".**..." //9
		};

char buffers[100][7];

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	while (true) {

		int D;
		scanf("%d", &D);
		if (D == 0)
			break;

		scanf("%s", buff);
		char c = buff[0];
		if (c == 'S') {
			scanf("%s", buff);
			for (int j = 0; j < 6; j += 2) {
				for (int i = 0; i < D; ++i) {
					int d = buff[i] - '0';
					if (i > 0)
						printf(" ");
					printf("%c%c", brailleDigits[d][j],
							brailleDigits[d][j + 1]);
				}
				printf("\n");
			}
		} else {

			for (int j = 0; j < 6; j += 2)
				for (int i = 0; i < D; ++i)
					scanf("%s", buffers[i] + j);
			for (int i = 0; i < D; ++i) {
				for (int k = 0; k < 10; ++k) {
					if (strncmp(brailleDigits[k], buffers[i], 6) == 0) {
						printf("%d", k);
						break;
					}
				}
			}
			printf("\n");
		}
	}

	return 0;
}