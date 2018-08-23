#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

char buffer[1500];

bool areEqual(char c1, char c2) {
	int val1 = ('a' <= c1 && c1 <= 'z') ? c1 - 'a' : c1 - 'A';
	int val2 = ('a' <= c2 && c2 <= 'z') ? c2 - 'a' : c2 - 'A';
	return val1 == val2;
}

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	while (true) {

		char cmp;

		//scanf(" %[^\n]",lineBuffer);

		bool first = true;
		bool yes = true;
		while (true) {

			scanf("%s", buffer);
			char c = getchar();
			if(first) {
				first = false;
				cmp = buffer[0];
				if(cmp == '*')
					return 0;
			} else {
				if(!areEqual(cmp,buffer[0])) {
					yes = false;
				}
			}
			if(c == '\n') {
				if(yes)
					printf("Y\n");
				else
					printf("N\n");
				break;
			}

		}

	}

	return 0;
}