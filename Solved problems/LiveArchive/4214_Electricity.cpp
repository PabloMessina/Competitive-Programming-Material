#include <cstdio>
#include <cstring>
using namespace std;

struct consumption {
	int d;
	int m;
	int y;
	int c;
};

bool isLeapYear(int year) {
	return ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
}
bool AreConsecutive(consumption A, consumption B) {
	if (A.y + 1 < B.y)
		return false;

	switch (A.m) {
	//31 days
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:

		if (A.d < 31) {
			if (A.d + 1 != B.d || A.m != B.m || A.y != B.y)
				return false;

		} else {
			if (B.d != 1)
				return false;
			if (A.m < 12) {
				if (A.m + 1 != B.m || A.y != B.y)
					return false;
			} else {
				if (B.m != 1 || B.y != A.y + 1)
					return false;
			}
		}

		break;
		//30 days
	case 4:
	case 6:
	case 9:
	case 11:

		if (A.d < 30) {
			if (A.d + 1 != B.d || A.m != B.m || A.y != B.y)
				return false;

		} else {
			if (B.d != 1)
				return false;
			if (A.m + 1 != B.m || A.y != B.y)
				return false;
		}
		break;

		//28-29 days (february)
	default:

		int maxDays = isLeapYear(A.y) ? 29 : 28;

		if (A.d < maxDays) {
			if (A.d + 1 != B.d || A.m != B.m || A.y != B.y)
				return false;

		} else {
			if (B.d != 1)
				return false;
			if (A.m + 1 != B.m || A.y != B.y)
				return false;
		}
		break;
	}
	return true;
}

int main() {
	while (true) {
		int n;
		scanf("%d", &n);
		if (n == 0)
			break;

		consumption before = {1, 1, 0, 0};

		int sum = 0;
		int count = 0;

		for (int i = 0; i < n; ++i) {
			consumption curr;
			scanf("%d %d %d %d", &curr.d, &curr.m, &curr.y, &curr.c);
			if (AreConsecutive(before, curr)) {
				sum += curr.c - before.c;
				count++;
			}
			before = curr;
		}

		printf("%d %d\n", count, sum);
	}
	return 0;
}