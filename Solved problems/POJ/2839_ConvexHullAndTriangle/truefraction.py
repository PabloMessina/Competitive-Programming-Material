def _gcd(a, b):
    if(b == 0):
        return a
    return _gcd(b, a % b)


def gcd(a, b):
    a, b = abs(a), abs(b)
    if(a < b):
        return _gcd(b, a)
    return _gcd(a, b)


class Fraction:
    def __init__(self, num, den=1):
        if(isinstance(num, Fraction)):
            self.num = num.num
            self.den = num.den
            return
        num = int(num)
        den = int(den)
        if(den < 0):
            num = -num
            den = -den
        g = gcd(num, den)
        self.num = num // g
        self.den = den // g
        if self.den == 0:
            raise ZeroDivisionError()

    def __repr__(self):
        return "{}/{}".format(self.num, self.den)

    def __add__(self, other):
        other = Fraction(other)
        return Fraction(self.num * other.den + other.num * self.den, self.den * other.den)

    def __mul__(self, other):
        other = Fraction(other)
        return Fraction(self.num * other.num, self.den * other.den)

    def __truediv__(self, other):
        other = Fraction(other)
        return Fraction(self.num * other.den, self.den * other.num)

    def __eq__(self, other):
        other = Fraction(other)
        return self.num == other.num and self.den == other.den

    def __neg__(self):
        return Fraction(-self.num, self.den)

    def __sub__(self, other):
        other = Fraction(other)
        return self + (-other)

    def __lt__(self, other):
        other = Fraction(other)
        return self.num * other.den < other.num * self.den

    def __le__(self, other):
        other = Fraction(other)
        return self < other or self == other

    def __gt__(self, other):
        other = Fraction(other)
        return not self <= other

    def __ge(self, other):
        other = Fraction(other)
        return self > other or self == other

    def __round__(self):
        result = self.num // self.den
        rem = self.num % self.den
        if rem * 2 >= self.den:
            result += 1
        if rem * 2 < -self.den:
            result -= 1
        return result

    def as_float(self):
        return self.num / self.den


if __name__ == "__main__":
    # print(gcd(-2, 4))
    a = Fraction(1, 7)
    b = Fraction(2, 14)
    print(a / b)
    print(Fraction(4, -2))
    print(Fraction(4, -2) == -Fraction(14, 7))
    print(round(Fraction(21, 2)))
