#include <cstdio>
#include <map>
using namespace std;

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	char c;

	int count = 0;
	int charsum = 0;

	while (true) {

		c = getchar();
		if (c == '*')
			return 0;
		else {

			switch (c) {

			case 'W':
				charsum += 64;
				break;
			case 'H':
				charsum += 32;
				break;
			case 'Q':
				charsum += 16;
				break;
			case 'E':
				charsum += 8;
				break;
			case 'S':
				charsum += 4;
				break;
			case 'T':
				charsum += 2;
				break;
			case 'X':
				charsum += 1;
				break;
			case '/':
				if (charsum == 64)
					count++;
				charsum = 0;
				break;
			case '\n':
				printf("%d\n", count);
				count = 0;
				c = getchar();
				if (c == '*')
					return 0;
				break;
			}

		}

	}

	return 0;

}
