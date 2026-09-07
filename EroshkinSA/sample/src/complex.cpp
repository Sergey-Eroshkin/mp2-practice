#include <iostream>
#include "complex.h"


Complex::Complex(double _re, double _im) : re(_re), im(_im) {}

std::istream& operator>>(std::istream& is, Complex& c) {
	is >> c.re >> c.im;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
	os << c.re << " + " << c.im << "i";
	return os;
}
