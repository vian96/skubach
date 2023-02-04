#include <iostream>

class Rational {
    int num_ = 0, denum_ = 0;

    Rational &simplify();

public:
    int num() const;
    int denum() const;

    Rational (int num, int denum);

    Rational &operator=(const Rational &other);

    int operator <=> (Rational const &other) const;

    Rational& operator++();

    // for some reason it is recommended to use (int)
    Rational operator++(int);
};

Rational operator+(Rational lhs, const Rational &rhs);

Rational operator-(Rational lhs, const Rational &rhs);

Rational operator*(Rational lhs, const Rational &rhs);

Rational operator/(Rational lhs, const Rational &rhs);

bool operator==(const Rational& l, const Rational& r);

std::ostream& operator<<(std::ostream& os, const Rational& r);
 
std::istream& operator>>(std::istream& is, Rational& r);

