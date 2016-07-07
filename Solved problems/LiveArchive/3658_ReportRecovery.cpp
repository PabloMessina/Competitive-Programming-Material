/**
 *	Algorithms used: Brute Force (backtracking + pruning)
 *	+ a lot of string manipulation
 */
#include <cstdio>
#include <string>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

#define FOR(i,i0,n) for(int i = i0; i < n; ++i)

int n_prods;
int n_sellers;
string sellerNames[4];
string sellerDigits[4];
string expectedTotals;

struct Substr {
	int offset;
	int length;
	int value;
};
Substr splits[4][6]; // 4 sellers x (5 products + total)
int totalSums[6];
char numBuff[50];

bool isDigit(char c) {
	return '0' <= c && c <= '9';
}

int substr2Int(const char* str, int offset, int length) {
	memcpy(numBuff, str + offset, length);
	numBuff[length] = '\0';
	return atoi(numBuff);
}

bool checkTable() {
	int offset = 0;
	FOR(i,0,n_prods+1) {
		int sum = 0;
		FOR(j,0,n_sellers) sum += splits[j][i].value;
		totalSums[i] = sum;
		sprintf(numBuff + offset,"%d",sum);
		offset = strlen(numBuff);
	}
	return strcmp(numBuff,expectedTotals.c_str()) == 0;
}

bool findSplit(int i_sel, int i_prod, int offset, int maxLenCarry) {
	string& digits = sellerDigits[i_sel];
	// not last seller
	if (i_sel < n_sellers - 1) {
		// product
		if (i_prod < n_prods) {
			int rest = digits.length() - offset - (n_prods - i_prod - 1) - maxLenCarry;
			int lengthLimit = 1 + ((rest > maxLenCarry) ?
				(maxLenCarry + (rest - maxLenCarry) / 2) : rest);
			FOR(length,1,lengthLimit) {
				if (digits[offset] == '0' && length > 1) break; // no leading 0's
				Substr& split = splits[i_sel][i_prod];
				split.offset = offset;
				split.length = length;
				split.value =  substr2Int(digits.c_str(), offset, length);

				if (findSplit(i_sel,i_prod+1,offset+length, max(maxLenCarry,length))) return true;
			}
		// total
		} else {
			int length = digits.length() - offset;
			if (digits[offset] == '0' && length > 1) return false; // no leading 0's
			// check this row's sum is correct
			int sum = 0;
			FOR(i,0,n_prods) sum += splits[i_sel][i].value;
			int total = substr2Int(digits.c_str(), offset, length);
			if (total == sum) {
				Substr& split = splits[i_sel][i_prod];
				split.offset = offset;
				split.length = length;
				split.value =  total;
				return findSplit(i_sel+1,0,0,0);
			}
		}
	// last seller
	} else {
		// product
		if (i_prod < n_prods) {
			int rest = digits.length() - offset - (n_prods - i_prod - 1) - maxLenCarry;
			int lengthLimit = 1 + ((rest > maxLenCarry) ?
				(maxLenCarry + (rest - maxLenCarry) / 2) : rest);
			FOR(length,1,lengthLimit) {
				if (digits[offset] == '0' && length > 1) break; // no leading 0's
				Substr& split = splits[i_sel][i_prod];
				split.offset = offset;
				split.length = length;
				split.value =  substr2Int(digits.c_str(), offset, length);
				if (findSplit(i_sel,i_prod+1,offset+length, max(maxLenCarry,length))) return true;
			}
		// total
		} else {
			int length = digits.length() - offset;
			if (digits[offset] == '0' && length > 1) return false; // no leading 0's
			// check this row's sum is correct
			int sum = 0;
			FOR(i,0,n_prods) sum += splits[i_sel][i].value;
			int total = substr2Int(digits.c_str(), offset, length);
			if (total == sum) {
				Substr& split = splits[i_sel][i_prod];
				split.offset = offset;
				split.length = length;
				split.value =  total;
				// check the whole assignment is correct
				return checkTable();
			}
		}
	}
	return false;
}

int main() {
	int cases;
	scanf("%d\n",&cases);
	string line;
	while(cases-- > 0) {
		// header
		getline(cin,line);
		n_prods = (line.length() - 6) / 2;
		// body
		n_sellers = 0;
		while (true) {
			getline(cin,line);
			if (memcmp(line.c_str(),"TP",2) == 0) {
				expectedTotals = line.substr(2);
				break;
			} else {
				FOR(i,0,line.length()) {
					if (isDigit(line[i])) {
						sellerNames[n_sellers] = line.substr(0,i);
						sellerDigits[n_sellers] = line.substr(i);
						break;
					}
				}
				n_sellers++;
			}
		}
		// find split
		findSplit(0,0,0,0);
		// print answer
		FOR(i,0,n_prods) printf("P%d ",i+1);
		puts("Totals");
		FOR(i,0,n_sellers) {
			printf("%s",sellerNames[i].c_str());
			FOR(j,0,n_prods+1) printf(" %d",splits[i][j].value);
			puts("");
		}
		printf("TP");
		FOR(i,0,n_prods+1) printf(" %d",totalSums[i]);
		puts("");
	}
	return 0;
}