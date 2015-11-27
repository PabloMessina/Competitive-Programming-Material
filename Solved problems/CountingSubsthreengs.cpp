#include <cstdio>
#include <cstring>
using namespace std;

typedef long long int ll;

bool isDigit(char c) {
	return '0' <= c && c <= '9';
}

int main() {

	while (true) {

		bool inside_number = false;
		ll mcount[3];
		ll backup[3];
		ll count = 0;
		bool hasfoundchars = false;

		while (true) {
			char c = getchar();

			if (c == '\n') {
				printf("%lld\n", count);
				break;
			}

			if (c == EOF) {
				if (hasfoundchars)
					printf("%lld\n", count);
				return 0;
			}

			hasfoundchars = true;

			if (isDigit(c)) {
				if (!inside_number)
					for (int i = 0; i <= 2; ++i)
						mcount[i] = 0;
				inside_number = true;
				memcpy(backup, mcount, sizeof mcount);
				int d = c - '0';
				for (int i = 0; i <= 2; ++i)
					mcount[(d + i) % 3] = backup[i];
				mcount[d % 3]++;
				count += mcount[0];
			} else {
				inside_number = false;
			}
		}
	}

	return 0;
}
