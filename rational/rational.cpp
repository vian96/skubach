#include "rational.h"

#include <numeric>
#include <iostream>
#include <stdexcept>

Rational& Rational::simplify() {
    if (denum_ == 0)
        throw std::overflow_error("Denumerator is zero");
    
    int sign = 1;
    if (num_ * denum_ < 0) 
        sign = -1;
    num_ = abs(num_);
    denum_ = abs(denum_);

    int gcd = std::gcd (num_, denum_);
    num_ = sign * num_ / gcd;
    denum_ = denum_ / gcd;
    
    return *this;
};

int Rational::num() const {
    return num_;
}

int Rational::denum() const {
    return denum_;
}

Rational::Rational (int num__, int denum__) : num_(num__), denum_(denum__) {
    simplify();
}

Rational operator+(Rational lhs, const Rational &rhs) {
    return Rational (lhs.num() * rhs.denum() + rhs.num() * rhs.denum(), lhs.denum() * rhs.denum());
}

Rational operator-(Rational lhs, const Rational &rhs) {
    return Rational (lhs.num() * rhs.denum() - rhs.num() * rhs.denum(), lhs.denum() * rhs.denum());
}

Rational operator*(Rational lhs, const Rational &rhs) {
    return Rational (lhs.num() * rhs.num(), lhs.denum() * rhs.denum());
}

Rational operator/(Rational lhs, const Rational &rhs) {
    if (rhs.num() == 0)
        throw std::overflow_error("Division by zero");

    return Rational (lhs.num() * rhs.denum(), lhs.denum() * rhs.num());
}

Rational& Rational::operator= (const Rational &other) {
    num_ = other.num_;
    denum_ = other.denum_;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Rational& r) {
    return os << r.num() << '/' << r.denum();
}
 
std::istream& operator>>(std::istream& is, Rational& r)
{
    int num = 0, denum = 0;
    is >> num >> denum;
    r = Rational (num, denum);
    return is;
}

Rational& Rational::operator++() {
    num_ += denum_;
    return *this; 
}

Rational Rational::operator++(int)
{
    Rational old = *this; 
    operator++();
    return old;
}

int Rational::operator <=> (Rational const &other) const {
    return (this->num_ * other.denum_ - other.num_ * this->denum_);
}

bool operator==(const Rational& l, const Rational& r) {
    return (l<=>r) == 0;
}
