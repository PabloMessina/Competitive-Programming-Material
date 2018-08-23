#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;

ll floor1_cost = 2 * 100;
ll floor2_cost = floor1_cost + 9900 * 3;
ll floor3_cost = floor2_cost + 990000 * 5;

ll floor1_cons = 100;
ll floor2_cons = 10000;
ll floor3_cons = 1000000;

ll getCost(ll consumption) {
	if (consumption <= floor1_cons) {
		return consumption * 2;
	}
	if (consumption <= floor2_cons) {
		return floor1_cost + (consumption - floor1_cons) * 3;
	}
	if (consumption <= floor3_cons) {
		return floor2_cost + (consumption - floor2_cons) * 5;
	}
	return floor3_cost + (consumption - floor3_cons) * 7;

}

ll binsearchCost(ll totalConsumption, ll billDelta) {

	ll i = 0;
	ll j = totalConsumption / 2;

	while (i < j) {
		ll m = (i + j) / 2;

//		ll mycons = m;
//		ll othercons = totalConsumption - m;
//		ll myCost = getCost(m);
//		ll otherCost = getCost(totalConsumption - m);
//		ll deltaCost = otherCost - myCost;

		ll deltaCost = abs(getCost(m) - getCost(totalConsumption - m));

//		printf("i = %d, j = %d, m = %d\n", i, j, m);
//		printf("\t myConsumption = %d\n", mycons);
//		printf("\t otherConsumption = %d\n", othercons);
//		printf("\t myCost = %d\n", myCost);
//		printf("\t otherCost = %d\n", otherCost);
//		printf("\t totalCost = %d\n", myCost + otherCost);
//		printf("\t delta = %d\n", deltaCost);

		if (deltaCost > billDelta) {
			i = m + 1;
		} else {
			j = m;
		}
	}

	return getCost(i);

}

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	while (true) {
		ll a, b;

		scanf("%lld %lld", &a, &b);
		if (a == 0 && b == 0)
			break;

//		printf("a = %d, b = %d,", a, b);

		ll consumption = 0;

		if (a <= floor1_cost) {
			consumption = a / 2;
		} else if (a <= floor2_cost) {
			consumption = floor1_cons;
			a -= floor1_cost;
			consumption += a / 3;
		} else if (a <= floor3_cost) {
			consumption = floor2_cons;
			a -= floor2_cost;
			consumption += a / 5;
		} else {
			consumption = floor3_cons;
			a -= floor3_cost;
			consumption += a / 7;
		}

//		printf(" consumption = %lld, cost = %lld\n", consumption,
//				getCost(consumption));

		printf("%lld\n", binsearchCost(consumption, b));

	}

	return 0;
}
