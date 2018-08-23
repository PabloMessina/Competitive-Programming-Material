#include <cstdio>
#include <cstring>
using namespace std;

int dead[100005];
int pointers[100005];

int main() {

//	setvbuf(stdout, NULL, _IONBF, 0);

	int isDead = 1;

	memset(dead, 0, sizeof dead);
	memset(pointers, 0, sizeof pointers);

	int B, S;
	while (scanf("%d %d", &S, &B) == 2 && S > 0 && B > 0) {

		for (int i = 0; i < B; ++i) {
			int L, R;
			scanf("%d %d", &L, &R);
			dead[L] = isDead;
			dead[R] = isDead;

			if (L > 1) {
				if (dead[L - 1] == isDead) {
					int ll = pointers[R] = pointers[L - 1];
					pointers[ll] = R;
					if (ll > 1)
						printf("%d", ll - 1);
					else
						printf("*");
				} else {
					pointers[L] = R;
					pointers[R] = L;
					printf("%d", L - 1);
				}
			} else {
				pointers[L] = R;
				pointers[R] = L;
				printf("*");
			}
			printf(" ");
			if (R < S) {
				if (dead[R + 1] == isDead) {
					int ll = pointers[R];
					int rr = pointers[R + 1];
					pointers[rr] = ll;
					pointers[ll] = rr;
					if (rr < S)
						printf("%d", rr + 1);
					else
						printf("*");
				} else {
					printf("%d", R + 1);
				}
			} else {
				printf("*");
			}
			printf("\n");
		}
		printf("-\n");
		isDead++;
	}
	return 0;
}
