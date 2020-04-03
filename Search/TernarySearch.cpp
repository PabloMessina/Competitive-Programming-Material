double cost(double x) { ... }

// find minimum (convex function)
double min_ternary_search(double l, double r, int times) {
    double c1, c2;
    while (times--) {
        double d = (r - l) / 3.0;
        double m1 = l + d;
        double m2 = r - d;
        c1 = cost(m1);
        c2 = cost(m2);
        if (c1 < c2) r = m2;
        else if (c2  < c1) l = m1;
        else l = m1, r = m2;
    }
    return (c1 + c2) * .5;
}

// finx maximum (concave function)
double max_ternary_search(double l, double r, int times) {
    double c1, c2;
    while (times--) {
        double d = (r - l) / 3.0;
        double m1 = l + d;
        double m2 = r - d;
        c1 = cost(m1);
        c2 = cost(m2);
        if (c1 < c2) l = m1;
        else if (c2  < c1) r = m2;
        else l = m1, r = m2;
    }
    return (c1 + c2) * .5;
}