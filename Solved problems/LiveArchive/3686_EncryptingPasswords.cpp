#include <cstdio>
#include <cstring>
using namespace std;

int n;
char message[401];

int main() {
	while (true) {
		scanf("%d", &n);
		if (n == 0) break;
		scanf("%s", message);

		int cols = n;
		int rows = strlen(message) / n;
		int offset = 6;
		int ascii = 0;

		// scan from uppermost row
		for (int c0 = 0; c0 < cols; ++c0) {
			for (int  c = c0, r = 0; c >= 0 && r < rows; c--, r++) {
				int index = r * cols + c;
				if (message[index] == '1') {
					ascii |= (1 << offset);
				}
				if (offset == 0) {
					if (ascii == 0) goto ending; //only zeros

					printf("%c", ascii);
					ascii = 0;
					offset = 6;
				} else {
					offset--;
				}
			}
		}

		// scan rightmost column
		for (int r0 = 1; r0 < rows; ++r0) {
			for (int  c = cols-1, r = r0; c >= 0 && r < rows; c--, r++) {
				int index = r * cols + c;
				if (message[index] == '1') {
					ascii |= (1 << offset);
				}
				if (offset == 0) {
					if (ascii == 0) goto ending; //only zeros

					printf("%c", ascii);
					ascii = 0;
					offset = 6;
				} else {
					offset--;
				}
			}
		}

		ending:
		puts("");
	}
}