/**
 * A lot of string manipulation
 */

const char* digits[10] = {
	"xxxxx"
	"x...x"
	"x...x"
	"x...x"
	"x...x"
	"x...x"
	"xxxxx",

	"....x"
	"....x"
	"....x"
	"....x"
	"....x"
	"....x"
	"....x",

	"xxxxx"
	"....x"
	"....x"
	"xxxxx"
	"x...."
	"x...."
	"xxxxx",

	"xxxxx"
	"....x"
	"....x"
	"xxxxx"
	"....x"
	"....x"
	"xxxxx",

	"x...x"
	"x...x"
	"x...x"
	"xxxxx"
	"....x"
	"....x"
	"....x",

	"xxxxx"
	"x...."
	"x...."
	"xxxxx"
	"....x"
	"....x"
	"xxxxx",

	"xxxxx"
	"x...."
	"x...."
	"xxxxx"
	"x...x"
	"x...x"
	"xxxxx",

	"xxxxx"
	"....x"
	"....x"
	"....x"
	"....x"
	"....x"
	"....x",

	"xxxxx"
	"x...x"
	"x...x"
	"xxxxx"
	"x...x"
	"x...x"
	"xxxxx",

	"xxxxx"
	"x...x"
	"x...x"
	"xxxxx"
	"....x"
	"....x"
	"xxxxx"
};

#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;

#define FOR(i,n) for(int i = 0; i < n; ++i)

bool peekAndCheck(char c) {
	char c2 = getchar();
	ungetc(c2, stdin);
	return c == c2;
}

char tokenBuffer[35];

char tokenBufferToChar() {
	FOR(d,10) if (strcmp(tokenBuffer, digits[d]) == 0) return (char)(d + '0');
	return '+';
}

bool isDigit(char c) {
	int d = c - '0';
	return 0 <= d && d <= 9;
}

void ASCII_print(int num) {
	vector<int> ds;
	while (num > 0) {
		ds.push_back(num % 10);
		num /= 10;
	}
	FOR(k,7) {
		int offset = k * 5;
		for (int i = ds.size() - 1; i >= 0; --i) {
			int d = ds[i];
			FOR(j,5) printf("%c", digits[d][offset + j]);
			if (i > 0) printf(".");
		}
		puts("");
	}
}

int main() {
	char c;
	do {
		// read 7 lines
		vector<string> lines(7);
		FOR(i,7) getline(cin, lines[i]);

		// parse tokens
		int n_tokens = (lines[0].size() + 1) / 6;  // num of tokemns
		int addend1 = 0;
		int addend2 = 0;
		bool plusConsumed = false;
		FOR(i, n_tokens) {
			// extract token from 7 lines
			int offset = 6 * i;
			int index = 0;
			FOR(j,7) FOR(k,5) tokenBuffer[index++] = lines[j][offset + k];
			char tokenChar = tokenBufferToChar(); // to char
			// process token
			if (isDigit(tokenChar)) {
				if (plusConsumed) {
					addend2 *= 10;
					addend2 += tokenChar - '0';
				} else {
					addend1 *= 10;
					addend1 += tokenChar - '0';
				}
			} else {
				plusConsumed = true;
			}
		}
		// print sum
		int sum = addend1 + addend2;
		ASCII_print(sum);

	} while (!peekAndCheck(EOF));
	return 0;
}