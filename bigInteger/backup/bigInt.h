/* 
	@author Matt Anderson
	@date March 18, 2020
	@brief C++ class for representing arbitratily big Integers and supporting basic
           operations on these integers   
*/
#ifndef BIGINT_INCLUDE_GUARD 
#define BIGINT_INCLUDE_GUARD
#include <vector>
#include <iostream>
#include <iomanip>

class bigInt {
	public:
		bigInt(long long i = 0) {
			if (i < 0) {
				i *= -1;
				negative = true;
			}
			else {
				negative = false;
			}
			while(i) {
				integer.push_back(i % base);
				i /= base;
			}
		}
		bigInt(const bigInt& rhs) {
			integer.resize(rhs.integer.size());
			std::copy(rhs.integer.begin(), rhs.integer.end(), integer.begin());
			negative = rhs.negative;
		}
		bigInt(bigInt&& rhs) {
			integer.swap(rhs.integer);
			negative = rhs.negative;
		}

		bool isNegative() const { return negative; }
		long long getBase() const { return base; }
		long long getNumBase10Digits() const;
		long long toInt64() const;
		bigInt& operator=(const bigInt& rhs);
		bigInt& operator=(bigInt&& rhs);
		bigInt& operator+=(const bigInt& rhs);
		bigInt& operator-=(const bigInt& rhs);
		bigInt& operator*=(const bigInt& rhs);
		bigInt& operator/=(const bigInt& rhs);
		bigInt operator++();
		bigInt operator++(int);
		bigInt operator--();
		bigInt operator--(int);
		bigInt operator+(const bigInt& rhs) const;
		bigInt operator-(const bigInt& rhs) const;
		bigInt operator-() const;
		bigInt operator*(const bigInt& rhs) const;
		bigInt operator/(const bigInt& rhs) const;
		bigInt operator^(const bigInt& rhs) const;
		bool operator<(const bigInt& rhs) const;
		bool operator>(const bigInt& rhs) const;
		bool operator==(const bigInt& rhs) const;
		bool operator!=(const bigInt& rhs) const;
		bool operator>=(const bigInt& rhs) const;
		bool operator<=(const bigInt& rhs) const;
		friend std::ostream& operator<<(std::ostream &out, const bigInt& i);

	private:
		const static long long base = 10;
		const static int digits = 1;
		std::vector<long long> integer;
		bool negative;

		bigInt divideByTwo(); // an operation only for use by member functions
		bool smaller(std::vector<long long>& d, std::vector<long long>& r, int start);
};
#endif
