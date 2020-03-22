#include "fraction.h"
#include <iostream>
//operator definitions

fraction& fraction::operator=(const fraction& rhs) {
	if (this == &rhs) { return *this; }
	n = rhs.n;
	d = rhs.d;
	negative = rhs.negative;
	std::cout << "Did an assignment copy" << std::endl;
	return *this;
}
fraction& fraction::operator+=(const fraction& rhs) {
	*this = *this + rhs;
	return *this;
}
fraction& fraction::operator-=(const fraction& rhs) {
	*this = *this - rhs;
	return *this;
}
fraction& fraction::operator*=(const fraction& rhs) {
	*this = *this * rhs;
	return *this;
}
fraction& fraction::operator/=(const fraction& rhs) {
	*this = *this * rhs;
	return *this;
}
fraction fraction::operator+(const fraction& rhs) const {
	fraction result;
	if (negative && rhs.negative) {
		result = fraction(-(n * rhs.d + d * rhs.n), d * rhs.d);
	}
	else if (negative) {
		result = fraction(d * rhs.n - n * rhs.d, d * rhs.d);
	}
	else if (rhs.negative) {
		result = fraction(n * rhs.d - d * rhs.n, d * rhs.d);
	}
	else {
		result = fraction(n * rhs.d + d * rhs.n, d * rhs.d);
	}
	return result;	
}
fraction fraction::operator-(const fraction& rhs) const {
	fraction result;
	if (negative && rhs.negative) {
		result = fraction(-(n * rhs.d - d * rhs.n), d * rhs.d);
	}
	else if (negative) {
		result = fraction(-(d * rhs.n + n * rhs.d), d * rhs.d);
	}
	else if (rhs.negative) {
		result = fraction(n * rhs.d + d * rhs.n, d * rhs.d);
	}
	else {
		result = fraction(n * rhs.d - d * rhs.n, d * rhs.d);
	}
	return result;
}
fraction fraction::operator*(const fraction& rhs) const {
	fraction result;
	if (negative && rhs.negative) {
		result = fraction(n * rhs.n, d * rhs.d);
	}
	else if (negative || rhs.negative) {
		result = fraction(-(n * rhs.n), d * rhs.d);
	}
	else {	
		result = fraction(n * rhs.n, d * rhs.d);
	}
	return result;
}
fraction fraction::operator/(const fraction& rhs) const {
	fraction result;
	if (negative && rhs.negative) {
		result = fraction(n * rhs.d, d * rhs.n);
	}
	else if (negative || rhs.negative) {
		result = fraction(-(n * rhs.d), d * rhs.n);
	}
	else {	
		result = fraction(n * rhs.d, d * rhs.n);
	}
	return result;
}
bool fraction::operator==(const fraction& rhs) const {
	if (n == rhs.n && d == rhs.d && negative == rhs.negative) { return true; }
	return false;
}
bool fraction::operator<(const fraction& rhs) const {
	if (*this == rhs) { return false; }
	if (negative) {
		if (rhs.negative) {
			if (n * rhs.d > rhs.n * d) { return true; }
			return false;
		}
		return true;
	}
	if (rhs.negative) {return false;}
	if (n * rhs.d < rhs.n * d) { return true; }
	return false;
}
bool fraction::operator>(const fraction& rhs) const {
	if (*this == rhs) { return false; }
	if (negative) {
		if (rhs.negative) {
			if (n * rhs.d < rhs.n * d) { return true; }
			return false;
		}
		return false;
	}
	if (rhs.negative) {return true;}
	if (n * rhs.d > rhs.n * d) { return true; }
	return false;

}
bool fraction::operator!=(const fraction& rhs) const {
	return !(*this == rhs);
}
