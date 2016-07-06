#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
using namespace std;
typedef unsigned long long int ull;

int main() {
	ull num, n;
	vector<int> remainders;
	vector<int> bases;
	while(true) {
		scanf("%llu", &num);
		if (num == 0) break;
		for (int b = 2; b <= 16; ++b) {
			n = num;
			do {
				remainders.push_back(n % b);
			} while ((n /= b) > 0);
			bool isPalindrom = true;
			for (int i = 0, j = remainders.size() - 1; i < j; ++i, --j) {
				if (remainders[i] != remainders[j]) {
					isPalindrom = false;
					break;
				}
			}
			if (isPalindrom) bases.push_back(b);
			remainders.clear();
		}
		if (bases.size() > 0) {
			printf("Number %llu is palindrom in basis", num);
			for (int i = 0; i < bases.size(); ++i) printf(" %d", bases[i]);
			puts("");
		} else {
			printf("Number %llu is not palindrom\n", num);
		}
		bases.clear();
	}
	return 0;
}