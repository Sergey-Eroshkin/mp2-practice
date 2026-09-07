#ifndef __COMPLEX_H_
#define __COMPLEX_H_

struct Complex {
	double re, im;
	Complex(double, double);
	Complex(const Complex&);
	Complex(const Complex&&);
	Complex operator+(const Complex&);
	Complex operator-(const Complex&);
	Complex operator*(const Complex&);
	Complex operator/(const Complex&);
	bool operator==(const Complex&) const;
	bool operator!=(const Complex&) const;
	const Complex& operator=(const Complex&);
	const Complex& operator+=(const Complex&);
	const Complex& operator-=(const Complex&);
	const Complex& operator*=(const Complex&);
	const Complex& operator/=(const Complex&);
	Complex& operator++();
	Complex& operator--();
	Complex operator-();
	friend std::ostream& operator<<(std::ostream&, const Complex&);
	friend std::istream& operator>>(std::istream&, Complex&);
}; 

#endif