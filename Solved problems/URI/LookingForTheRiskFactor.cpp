// tags: math, sieve of eratosthenes, primes, fenwick tree, sort queries
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef tuple<int,int,int> iii;
// -------------------------------

const int MAXN = 100000;
const int MAXQ = 50000;

// sieve of eratosthenes
vector<int> get_primes_up_to(int n) {
	vector<bool> is_prime(n + 1, true);
	int limit = (int) floor(sqrt(n));
	rep (i,2,limit)
		if (is_prime[i])
			for (int j = i * i; j <= n; j += i)
				is_prime[j] = false;
	vector<int> primes;
	rep(i,2,n) if (is_prime[i]) primes.push_back(i);
	return primes;
}

struct BIT { // binary indexed tree, aka fenwick tree
	vector<int> ft;
	BIT(int n) { ft.assign(n+1, 0); }
	// prefix sum query (sum in range 1 .. b)
	int psq(int b) {
        int sum = 0;
        for (; b; b -= (b & -b)) sum += ft[b];
        return sum;
	}
	// range sum query (sum in range a .. b)
	int rsq(int a, int b) {
        return psq(b) - psq(a-1);
	}
	// increment k'th value by v (and propagate)
	void add(int k, int v) {
        for (; k < ft.size(); k += (k & -k)) ft[k] += v;
	}
};

int answers[MAXQ]; // to save query answers
bool divisible[MAXN+1]; // divisible[x] = x is divisble by a prime > k
// where k is a variable defined later on

int main() {
    // collect all primes for the problem
    vector<int> primes = get_primes_up_to(MAXN);    
    int Q;
    while (cin >> Q) { // for each test case
        // read and collect queries
        vector<iii> queries;
        queries.reserve(Q);
        rep(i,0,Q-1) {
            int n, k; cin >> n >> k;
            queries.emplace_back(k,n,i); // we include 'i' to remember original index
        }
        // sort queries in decreasing order of 'k'
        sort(queries.begin(), queries.end(), greater<iii>());
        // init fenwick tree
        BIT ft(MAXN);
        // reset divisible array
        memset(divisible, 0, sizeof divisible);
        // answer queries
        int i = primes.size() - 1; // we check from the largest prime backwards
        for (auto& q : queries) {
            int k = get<0>(q);
            int n = get<1>(q);
            int index = get<2>(q);
            // for each primes[i] > k not considered in previous iterations
            //   we annotate all numbers divisible by it (i.e. multiples of primes[i])
            while (i >= 0 and primes[i] > k) {
                for (int x = primes[i]; x <= MAXN; x += primes[i]) {
                    if (!divisible[x]) {
                        divisible[x] = true; // x is divisible by a prime > k
                        ft.add(x, 1); // record this in fenwick tree
                    }
                }
                i--;
            }
            // the answer is the whole range [2, n] - the numbers divisible
            // by primes > k
            answers[index] = n - 1 - ft.rsq(2, n);
        }
        // write answers in original order
        rep(i,0,Q-1) cout << answers[i] << endl;
    }
    return 0;
}