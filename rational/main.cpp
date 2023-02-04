#include "rational.h"

#include <iostream>

int main() {
    Rational a(1,3), b(2,6), c(1,1);

    std::cin >> c;
    
    std::cout << (a!=b) << a << b << c << a+b << a*b << a/b << a+b << a-b << a*c << c/b << a++ << ++b << std::endl;
}

// test
// IN 12 12
// OUT 01/31/31/12/31/91/12/30/11/33/11/34/3
       
