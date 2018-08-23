#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;

int hand[3];
int hand2[3];

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	int A, B, C;

	while (scanf("%d %d %d", &A, &B, &C) == 3 && A && B && C) {

		hand[0] = A;
		hand[1] = B;
		hand[2] = C;

		sort(hand, hand + 3);

		if (hand[0] == hand[1] && hand[1] == hand[2]) {
			int val = hand[0];
			if (val < 13) {
				val++;
				printf("%d %d %d\n", val, val, val);
			} else
				printf("*\n");
		} else if (hand[0] == hand[1] || hand[1] == hand[2]) {

			int val_d, val_s;
			if (hand[0] == hand[1]) {
				val_d = hand[0];
				val_s = hand[2];
			} else {
				val_d = hand[1];
				val_s = hand[0];
			}

			if (val_s < 13) {
				val_s++;
				if (val_s == val_d) {
					if (val_s < 13) {
						val_s++;
						printf("%d %d %d\n", val_d, val_d, val_s);
					} else {
						printf("1 1 1\n");
					}

				} else {
					hand2[0] = hand2[1] = val_d;
					hand2[2] = val_s;
					sort(hand2, hand2 + 3);
					printf("%d %d %d\n", hand2[0], hand2[1], hand2[2]);
				}
			} else {
				val_d++;
				val_s = 1;
				hand2[0] = hand2[1] = val_d;
				hand2[2] = val_s;
				sort(hand2, hand2 + 3);
				printf("%d %d %d\n", hand2[0], hand2[1], hand2[2]);
			}
		} else {
			printf("1 1 2\n");
		}

	}
	return 0;
}