/* 
  @author Matt Anderson
  @date March 17, 2020 
  @brief C++ class for representing fractions.
*/
#ifndef FRACTION_CLASS_HEADER_GUARD
#define FRACTION_CLASS_HEADER_GUARD
#include <cstdint>
#include <iostream>

class fraction {
	public:

	fraction(uint64_t top, uint64_t bot) {
		uint64_t commonDenominator = gcd(top, bot);
		n = top / commonDenominator;
		d = bot / commonDenominator;
		negative = false; 
		std::cout << "called constructor for uints.." << std::endl;
	}
	fraction() {}
	fraction(int64_t top, int64_t bot) {
		uint64_t commonDenominator = gcd(top, bot);
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
	fraction(int top, int bot) : fraction(static_cast<int64_t>(top), static_cast<int64_t>(bot)) {}	
	
	uint64_t getNumerator() const { return n; }
	uint64_t getDenominator() const { return d; }
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
	uint64_t d;       //denominator
	uint64_t n;       //numerator
	bool negative;    //flag if fraction is negative
	
	//euclid's algorithm for finding the greatest common denominator	
	uint64_t gcd (uint64_t a, uint64_t b) {
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
