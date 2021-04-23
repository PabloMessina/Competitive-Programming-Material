/* ========================= */
/* Ternary Search on Doubles */
/* ========================= */
double f(double x) { ... }
// find minimum (convex function)
double min_ternary_search(double l, double r, int times) {
    while (times--) {
        double d = (r - l) / 3.0;
        double m1 = l + d, m2 = r - d;
        double f1 = f(m1), f2 = f(m2);
        if (f1 <= f2) r = m2;
        if (f1 >= f2) l = m1;
    }
    return f((l+r)*.5);
}
// find maximum (concave function)
double max_ternary_search(double l, double r, int times) {
    while (times--) {
        double d = (r - l) / 3.0;
        double m1 = l + d, m2 = r - d;
        double f1 = f(m1), f2 = f(m2);
        if (f1 >= f2) r = m2;
        if (f1 <= f2) l = m1;
    }
    return f((l+r)*.5);
}

/* ========================== */
/* Ternary Search on Integers */
/* ========================== */
int f(int i) { ... }
int min_search(int l, int r) { // convex function
    while (l < r) {
        int m = (i+j) >> 1;
        if (f(m+1) >= f(m)) r = m;
        else l = m+1;
    }
    return l;
}
int max_search(int l, int r) { // concave function
    while (l < r) {
        int m = (i+j) >> 1;
        if (f(m+1) <= f(m)) r = m;
        else l = m+1;
    }
    return l;
}