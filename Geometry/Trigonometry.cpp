/* ================= */
/* Angle of a vector */
/* ================= */
const double PI = acos(-1);
const double _2PI = 2 * PI;

double correct_angle(double angle) { // to ensure 0 <= angle <= 2PI
    while (angle < 0) angle += _2PI;
    while (angle > _2PI) angle -= _2PI;
    return angle;
}
double angle(double x, double y) {
    // atan2 by itself returns an angle in range [-PI, PI]
    // no need to "correct it" if that range is ok for you
    return correct_angle(atan2(y, x));
}

/* ============== */
/* Cosine Theorem */
/* ============== */
// Given triangle with sides a, b and c, returns the angle opposed to side a.
// a^2 = b^2 + c^2 - 2*b*c*cos(alpha)
// => alpha = acos((b^2 + c^2 - a^2) /(2*b*c))
double cos_theorem_angle(double a, double b, double c) {
    return acos((b*b + c*c - a*a)/(2*b*c));
}