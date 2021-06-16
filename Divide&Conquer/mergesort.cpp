void mergesort_(vector<int>& a, int i, int j, vector<int>& b) {
    if (i == j) return; // caso base
    // caso general
    int m = (i+j)/2;
    mergesort_(a, i, m, b);
    mergesort_(a, m+1, j, b);
    // merge eficiente
    int r = i, s = m+1;
    int k = i;
    while (r <= m and s <= j) b[k++] = a[r] <= a[s] ? a[r++] : a[s++];
    while (r <= m) b[k++] = a[r++];
    while (s <= j) b[k++] = a[s++];
    for (int x = i; x <= j; ++x) a[x] = b[x];
}

void mergesort(vector<int>& a) {
    vector<int> b(a.size());
    mergesort_(a, 0, a.size()-1, b);
}

sort(a.begin(), a.end()); // con la stl
