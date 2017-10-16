#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <random>
using namespace std;

int main() {
    int times = 1000;
    srand (time(NULL));
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    while (times--) {
        int R = rand() % 10 + 1;
        int C = rand() % 10 + 1;
        printf("%d %d\n", R, C);
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (dis(gen) <= 0.7) {
                    putchar('#');
                } else {
                    putchar('.');
                }
            }
            puts("");
        }
        puts("");
    }
    puts("0 0");
    return 0;
}