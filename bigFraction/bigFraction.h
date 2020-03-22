/* 
  @author Matt Anderson
  @date March 17, 2020 
  @brief C++ class for representing fractions.
*/
#ifndef FRACTION_CLASS_HEADER_GUARD
#define FRACTION_CLASS_HEADER_GUARD
#include <cstdint>
#include <iostream>
#include "bigInt.h"

class fraction {
	public:

	fraction() {}
	fraction(bigInt number) {
		if (number.isNegative()) {
			n = -number;
			negative = true;
		}
		else {
			n = number;
			negative = false;
		}
		d = bigInt(1);
	}
	fraction(bigInt top, bigInt bot) {
		bigInt commonDenominator = gcd(top, bot);
		if ((top >= 0 && bot > 0) || (top < 0 && bot < 0)) { 
			negative = false;
		}
		else if (top < 0) {
			top = -top;
			negative = true;
		}
		else {
			bot = -bot;
			negative = true;
		}	
			n = top / commonDenominator;
			d = bot / commonDenominator;
	}
	
	bigInt getNumerator() const { return n; }
	bigInt getDenominator() const { return d; }
	bool isNegative() const { return negative; }
	
	fraction& operator=(const fraction& rhs);
	fraction& operator+=(const fraction& rhs);
	fraction& operator-=(const fraction& rhs);
	fraction& operator*=(const fraction& rhs);
	fraction& operator/=(const fraction& rhs);
	fraction operator+(const fraction& rhs) const;
	fraction operator-(const fraction& rhs) const;
	fraction operator*(const fraction& rhs) const;
	fraction operator/(const fraction& rhs) const;
	bool operator==(const fraction& rhs) const;
	bool operator!=(const fraction& rhs) const;
	bool operator<(const fraction& rhs) const;
	bool operator>(const fraction& rhs) const;

private:
	bigInt d;       //denominator
	bigInt n;       //numerator
	bool negative;    //flag if fraction is negative
	
	//euclid's algorithm for finding the greatest common denominator	
	bigInt gcd (bigInt a, bigInt b) {
		while (a != b) {
			if (a > b) {
				a -= b;
			}
			else {
				b -= a;
			}
		}
		return a;
	}

};

#endif
