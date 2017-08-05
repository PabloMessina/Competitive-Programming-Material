struct FenwickTree {
	vector<int> ft;
	FenwickTree(int n) { ft.assign(n+1, 0); }
	// prefix sum query (sum in range 1 .. b)
	int psq(int b) {
		int sum = 0;
		for (; b; b -= (b & -b)) sum += ft[b];
		return sum;
	}
	// range sum query (sum in range a .. b)
	int rsq(int a, int b) {
		return rsq(b) - (a == 1 ? 0 : rsq(a-1));
	}
	// increment k'th value by v (and propagate)
	void add(int k, int v) { 
		for (; k < ft.size(); k += (k & -k)) ft[k] += v;
	}
	// increment range [i ... j] with v (and propagate)
	void range_add(int i, int j, int v) {
		add(i, v);
		add(j+1, -v);
	}
};