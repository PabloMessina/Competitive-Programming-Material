//=========================================================
// Modular Fibonacci with (Modular) Matrix Exponentiation
//=========================================================
//source: http://mathoverflow.net/questions/40816/fibonacci-series-mod-a-number
#include <cstdio>
#include <vector>
using namespace std;
typedef unsigned long long ull;
const ull MOD = 1000000000;

vector<ull> mult(const vector<ull>& A, const vector<ull>& B) {
	vector<ull> res 
	{ (((A[0] * B[0]) % MOD) + ((A[1] * B[2]) % MOD)) % MOD, //m11
		(((A[0] * B[1]) % MOD) + ((A[1] * B[3]) % MOD)) % MOD, //m12
		(((A[2]	* B[0]) % MOD) + ((A[3] * B[2]) % MOD)) % MOD, //m21
		(((A[2]	* B[1]) % MOD) + ((A[3] * B[3]) % MOD)) % MOD //m22
	};
	return res;
}

vector<ull> raise(const vector<ull>& matrix, ull exp) {
	if (exp == 1)
		return matrix;
	ull m = exp / 2;
	vector<ull> A = raise(matrix, m);
	if (exp % 2 == 0)
		return mult(A, A);
	else
		return mult(mult(A, A), matrix);
}

int main() {
	int P;
	int k;
	ull y;
	scanf("%d", &P);
	vector<ull> fib_matrix { 1, 1, 1, 0 }; //starting fibonacci matrix [f2, f1, f1, f0]
	while (P-- > 0) {
		scanf("%d %llu", &k, &y);
		vector<ull> ansm = raise(fib_matrix, y);
		ull ans = ansm[1];
		printf("%d %llu\n", k, ans);
	}
	return 0;
}
