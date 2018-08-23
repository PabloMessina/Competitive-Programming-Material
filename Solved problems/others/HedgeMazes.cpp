#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
using namespace std;

char brailleBuff[3][400];
char buff[200];

char brailleAnswers[10][10] = { ".***..", "*.....", "*.*...", "**....", "**.*..",
		"*..*..", "***...", "****..", "*.**..", ".**..." };

int R,C,Q;

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	while (true) {


		scanf("%d %d %d", &R,&C,&Q);
		if (R+C+Q == 0)
			break;

		char c;
		scanf("%s",buff);
		c = buff[0];

//		printf("c == %c\n", c);

		if (c == 'S') { //decimal digits
			scanf("%s", buff);

			for (int i = 0; i < D; ++i) {
				int d = buff[i] - '0';
//				printf("\td = %d\n", d);
//				printf("\t%.*s\n", 2, brailleAnswers[d]);
//				printf("\t%.*s\n", 2, brailleAnswers[d] + 2);
//				printf("\t%.*s\n", 2, brailleAnswers[d] + 4);
				memcpy(&brailleBuff[0][i * 3], brailleAnswers[d], 2);
				memcpy(&brailleBuff[1][i * 3], brailleAnswers[d] + 2, 2);
				memcpy(&brailleBuff[2][i * 3], brailleAnswers[d] + 4, 2);
			}
			printf("%.*s\n", D * 3 - 1, brailleBuff[0]);
			printf("%.*s\n", D * 3 - 1, brailleBuff[1]);
			printf("%.*s\n", D * 3 - 1, brailleBuff[2]);

		} else { //Braille

			for (int i = 0; i < 3; ++i) {
				scanf(" %[^\n]", buff);
//				printf("buff = %s\n", buff);
				memcpy(brailleBuff[i], buff, D * 3 - 1);
			}

			for (int i = 0; i < D; ++i) {
				memcpy(buff, &brailleBuff[0][i * 3], 2);
				memcpy(buff + 2, &brailleBuff[1][i * 3], 2);
				memcpy(buff + 4, &brailleBuff[2][i * 3], 2);

//				printf("i == %d, buff = %.*s\n", i, 6, buff);

				for (int j = 0; j < 10; ++j) {
//					printf("j = %d, buff = %.*s, braillAns[j] = %.*s\n", j, 6,
//							buff, 6, brailleAnswers[j]);
					if (strncmp(buff, brailleAnswers[j], 6) == 0) {
						printf("%d", j);
						break;
					}
				}
			}
			printf("\n");

		}

	}

	return 0;
}
