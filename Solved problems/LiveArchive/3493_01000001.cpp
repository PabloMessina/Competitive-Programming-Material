// tags: implementation
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

char buff1[81];
char buff2[81];

int main() {
	int cases;
	scanf("%d", &cases);
	int _case = 1;
	while(cases-- > 0) {
		scanf("%s %s",buff1,buff2);
		int len1 = strlen(buff1);
		int len2 = strlen(buff2);
		int carry = 0;
		vector<char> answer;
		// common length
		for (int i1 = len1 - 1, i2 = len2 - 1; (i1 >= 0) && (i2 >= 0); --i1, --i2) {
			int bitsum = carry + (buff1[i1] - '0') + (buff2[i2] - '0');
			if (bitsum == 3) {
				answer.push_back('1');
				carry = 1;
			} else if (bitsum == 2) {
				answer.push_back('0');
				carry = 1;
			} else {
				answer.push_back((char)(bitsum + '0'));
				carry = 0;
			}
		}
		// overflow part
		if (len1 > len2) {
			for (int i = len1 - 1 - len2; i >= 0; --i) {
				int bitsum = carry + (buff1[i] - '0');
				if (bitsum == 2) {
					answer.push_back('0');
					carry = 1;
				} else {
					answer.push_back((char)(bitsum + '0'));
					carry = 0;
				}
			}
		} else if (len2 > len1) {
			for (int i = len2 - 1 - len1; i >= 0; --i) {
				int bitsum = carry + (buff2[i] - '0');
				if (bitsum == 2) {
					answer.push_back('0');
					carry = 1;
				} else {
					answer.push_back((char)(bitsum + '0'));
					carry = 0;
				}
			}
		}
		// if carry still remaining
		if (carry) answer.push_back('1');
		// remove leading zeroes
		while (answer.size() > 1 && answer.back() == '0') answer.pop_back();
		// print answer
		printf("%d ", _case++);
		for (int i = answer.size() - 1; i >= 0; --i) printf("%c", answer[i]);
		puts("");
	}
	return 0;
}