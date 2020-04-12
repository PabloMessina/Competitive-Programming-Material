double f(double x) { ... }
// find minimum (convex function)
double min_ternary_search(double l, double r, int times) {
    while (times--) {
        double d = (r - l) / 3.0;
        double m1 = l + d;
        double m2 = r - d;
        if (f(m1) < f(m2)) r = m2;
        else l = m1;
    }
    return f((l+r).5);
}
// finx maximum (concave function)
double max_ternary_search(double l, double r, int times) {
    while (times--) {
        double d = (r - l) / 3.0;
        double m1 = l + d;
        double m2 = r - d;
        if (f(m1) > f(m2)) r = m2;
        else l = m1;
    }
    return f((l+r).5);
}