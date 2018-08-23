#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
#include <sstream>
using namespace std;

char buff1[100];
char buff2[100];

int digitsCount[10];

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	while (true) {

		scanf("%s %s", buff1, buff2);
		if (buff1[0] == '0' && buff2[0] == '0')
			break;

		string s1(buff1);
		string s2(buff2);

		memset(digitsCount, 0, sizeof digitsCount);

		int fac = 1;
		int num2 = atoi(buff2);
		for (int i = s2.length() - 1; i >= 0; --i) {

			int d = s2[i] - '0';

			num2 /= 10;

			if (i > 0) {
				for (int k = 1; k <= 9; ++k) {
					digitsCount[k] += num2 * fac;
				}
				digitsCount[0] += (num2 - 1) * fac;
			}

			if (i > 0) {
				for (int k = 0; k < d; ++k) {
					digitsCount[k] += fac;
				}
			} else {
				for (int k = 1; k < d; ++k) {
					digitsCount[k] += fac;
				}
			}

			if (i < (int) s2.length() - 1) {
				digitsCount[d] += atoi(s2.c_str() + i + 1) + 1;
			} else {
				digitsCount[d]++;
			}

			fac *= 10;
		}

		int num1 = atoi(buff1);
		num1--;

		if (num1 > 0) {

			stringstream ss;
			ss << num1;
			s1 = ss.str();

			int fac = 1;
			for (int i = s1.length() - 1; i >= 0; --i) {

				int d = s1[i] - '0';

				num1 /= 10;

				if (i > 0) {
					for (int k = 1; k <= 9; ++k) {
						digitsCount[k] -= num1 * fac;
					}
					digitsCount[0] -= (num1 - 1) * fac;
				}

				if (i > 0) {
					for (int k = 0; k < d; ++k) {
						digitsCount[k] -= fac;
					}
				} else {
					for (int k = 1; k < d; ++k) {
						digitsCount[k] -= fac;
					}
				}

				if (i < (int) s1.length() - 1) {
					digitsCount[d] -= atoi(s1.c_str() + i + 1) + 1;
				} else {
					digitsCount[d]--;
				}

				fac *= 10;
			}
		}

		for (int i = 0; i < 10; ++i) {
			if (i)
				printf(" %d", digitsCount[i]);
			else
				printf("%d", digitsCount[i]);
		}
		printf("\n");

	}

	return 0;
}
