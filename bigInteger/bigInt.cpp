#include "bigInt.h"

long long bigInt::toInt64() const {
	long long value = 0;
	long long factor = 1;
	for (int i = 0; i < integer.size(); i++) {
		value += integer[i] * factor;
		factor *= base;
	}
	if (negative) { return -value; }
	else { return value; } 	
}
long long bigInt::getNumBase10Digits() const {
	long long numDigits = static_cast<long long>(integer.size() - 1) * digits;

	// add the base 10 digits in the final bigNum digit
	long long finalDigit = integer[integer.size() - 1];
	long long count = 0;
	while (finalDigit > 0) {
		count++;
		finalDigit /= 10;
	}

	return numDigits + count;
}
bigInt& bigInt::operator=(const bigInt& rhs) {
	if (this == &rhs) { return *this; }
	integer.resize(rhs.integer.size());
	std::copy(rhs.integer.begin(), rhs.integer.end(), integer.begin());
	negative = rhs.negative;
	return *this;
}
bigInt& bigInt::operator=(bigInt&& rhs) {
	if (this == &rhs) { return *this; }
	integer.swap(rhs.integer);
	negative = rhs.negative;
	return *this;
}
bigInt& bigInt::operator+=(const bigInt& rhs) {
	*this = *this + rhs;
	return *this ;
}
bigInt& bigInt::operator-=(const bigInt& rhs) {
	*this = *this - rhs;
	return *this;
}
bigInt& bigInt::operator*=(const bigInt& rhs) {
	*this = *this * rhs;
	return *this;
}
bigInt& bigInt::operator/=(const bigInt& rhs) {
	*this = *this / rhs;
	return *this;
}
bigInt bigInt::operator++() {
	if (negative) {
		long long carry = 1;
		int index = 0;
		while (carry) {
			if (integer[index] - carry < 0) {
				integer[index] = base - carry;
				index++;
			}
			else {
				integer[index] -= carry;
				carry = 0;
			}
		}
		if (integer[integer.size() - 1] == 0) { 
			if (integer.size() == 1) { negative = false; }
			else { integer.pop_back(); }
		}
		bigInt toReturn(*this);
		return toReturn;
	}
	else {
		long long carry = 1;
		int index = 0;
		while (carry) {
			if (index == integer.size()) {
				integer.push_back(1);
				carry = 0;
			}
			else if (integer[index] + carry >= base) {
				integer[index] = 0;
				index++;
			}
			else {
				integer[index] += carry;
				carry = 0;
			}
		}
		bigInt toReturn(*this);
		return toReturn;
	}
}
bigInt bigInt::operator++(int) {
	if (negative) {
		bigInt toReturn(*this);
		long long carry = 1;
		int index = 0;
		while (carry) {
			if (integer[index] - carry < 0) {
				integer[index] = base - carry;
				index++;
			}
			else {
				integer[index] -= carry;
				carry = 0;
			}
		}
		if (integer[integer.size() - 1] == 0) { 
			if (integer.size() == 1) { negative = false; }
			else { integer.pop_back(); }
		}
		return toReturn;
	}
	else {
		bigInt toReturn(*this);
		long long carry = 1;
		int index = 0;
		while (carry) {
			if (index == integer.size()) {
				integer.push_back(1);
				carry = 0;
			}
			else if (integer[index] + carry >= base) {
				integer[index] = 0;
				index++;
			}
			else {
				integer[index] += carry;
				carry = 0;
			}
		}
		return toReturn;
	}
}
bigInt bigInt::operator--() {
	if (negative) {
		long long carry = 1;
		int index = 0;
		while (carry) {
			if (index == integer.size()) {
				integer.push_back(1);
				carry = 0;
			}
			else if (integer[index] + carry >= base) {
				integer[index] = 0;
				index++;
			}
			else {
				integer[index] += carry;
				carry = 0;
			}
		}
		bigInt toReturn(*this);
		return toReturn;
	}
	else {
		if (integer.size() == 1) {
			if (integer[0] == 0) {
				integer[0] = 1;
				negative = true;
				return bigInt(*this);
			}
			else if (integer[0] == 1) {
				integer[0] = 0;
				return bigInt(*this);
			}
		}
		long long carry = 1;
		int index = 0;
		while (carry) {
			if (integer[index] - carry < 0) {
				integer[index] = base - carry;
				index++;
			}
			else {
				integer[index] -= carry;
				carry = 0;
			}
		}
		if (integer[integer.size() - 1] == 0) { integer.pop_back(); }
	
	bigInt toReturn(*this);
	return toReturn;
	}
}
bigInt bigInt::operator--(int) {
	if (negative) {
		bigInt toReturn(*this);
		long long carry = 1;
		int index = 0;
		while (carry) {
			if (index == integer.size()) {
				integer.push_back(1);
				carry = 0;
			}
			else if (integer[index] + carry >= base) {
				integer[index] = 0;
				index++;
			}
			else {
				integer[index] += carry;
				carry = 0;
			}
		}
		return toReturn;
	}
	else {
		if (integer.size() == 1) {
			if (integer[0] == 0) {
				bigInt ret(*this);
				integer[0] = 1;
				negative = true;
				return ret;
			}
			else if (integer[0] == 1) {
				bigInt ret(*this);
				integer[0] = 0;
				return ret;
			}
		}
		bigInt toReturn(*this);
		long long carry = 1;
		int index = 0;
		while (carry) {
			if (integer[index] - carry < 0) {
				integer[index] = base - carry;
				index++;
			}
			else {
				integer[index] -= carry;
				carry = 0;
			}
		}
		if (integer[integer.size() - 1] == 0) { integer.pop_back(); }
		return toReturn;
	}
}
bigInt bigInt::operator+(const bigInt& rhs) const {
	if (negative == rhs.negative) {
		if (rhs.integer.size() > integer.size()) { return (rhs + *this); }
		else {
			bigInt newInt = rhs;
			int carry = 0;
			if (newInt.integer.size()  < integer.size()) {
				newInt.integer.resize(integer.size(), 0);
			}
			for (int i = 0; i < integer.size(); i++) {
				long long temp = integer[i] + newInt.integer[i] + carry;
				if (temp >= base) {
					carry = 1;
					temp -= base;
				}
				else {
					carry = 0;
				}
				newInt.integer[i] = temp;
			}
			if (carry == 1) { newInt.integer.push_back(1); }
			return newInt;
		}
	}
	return (*this - (-rhs));
}
bigInt bigInt::operator-(const bigInt& rhs) const {
	if (negative == rhs.negative) {
		if (rhs > *this) { return -(rhs - *this); }
		else {
			bigInt newInt = rhs;
			int carry = 0;
			if (newInt.integer.size() < integer.size()) {
				newInt.integer.resize(integer.size(), 0);
			}
			for (int i = 0; i < integer.size(); i++) {
				long long temp = integer[i] - newInt.integer[i] + carry;
				if (temp < 0) {
					temp = base + integer[i] - newInt.integer[i] + carry;
					carry = -1;
				}
				else {
					carry = 0;
				}
				newInt.integer[i] = temp;
			}
			// eliminate any empty spaces in the vector
			for (int i = newInt.integer.size() - 1; i >= 0; i--) {
				if (newInt.integer[i] == 0) { newInt.integer.pop_back(); }
				else { break; }
			}
			return newInt;
		}
	}
	else { return *this + (-rhs); }
}
bigInt bigInt::operator-() const {
	bigInt newVal = *this;
	if(negative) { newVal.negative = false; }
	else { newVal.negative = true; }
	return newVal;
}
bigInt bigInt::operator*(const bigInt& rhs) const {
	bigInt newInt;
	
	// give product the correct sign
	if (negative != rhs.negative) { newInt.negative = true; }

	// compute partial products
	std::vector<long long> product(integer.size() + rhs.integer.size(), 0);
	for (int i = 0; i < integer.size(); i++) {
		
		// compute digit and carry from partial product, and add to product
		int j;
		long long carry = 0;
		for (j = 0; j < rhs.integer.size(); j++) {
			long long digit = integer[i] * rhs.integer[j] + carry;
			carry = digit / base;
			digit %= base; 
			product[i + j] += digit;

			// check for overflow
			if (product[i + j] >= base) { 
				carry += 1;
				product[i + j] -= base;
			}
		}

		//check for carry from last partial product digit
		if (carry != 0) { product[i + j] += carry; }
	}

	// if highest order digit has value of zero remove 
	if (product[integer.size() + rhs.integer.size() - 1] == 0) { product.pop_back(); }

	newInt.integer = product;
	return newInt;
}
bigInt bigInt::operator/(const bigInt& rhs) const {
	if (*this < rhs) { return bigInt(0); }
	if (*this == rhs) { return bigInt(1); }
	if (integer.size() == 1) { return integer[0] / rhs.integer[0]; }

	bigInt r(*this);
	bigInt quotient;
	quotient.integer.resize(integer.size() - rhs.integer.size() + 1, 0);
	
	// determine negativity
	if (negative == rhs.negative) { quotient.negative = false; }
	else { quotient.negative = true; }


	// iterate over the digits in number to divide starting with the most 
	// significant digit
	long long carry = 0;
	for (int i = integer.size() - 1; i >= static_cast<int>(rhs.integer.size()) - 1; i--) {

		// add carry to the current remainder digit
		r.integer[i] += carry * base;
		
		// get initial estimate of multiples
		long long multiples = (r.integer[i]) / rhs.integer[rhs.integer.size() - 1];
		long long rem = r.integer[i] % rhs.integer[rhs.integer.size() - 1];
		
		// check estimate against next digit (if rhs has more than 1 digit)
		if (rhs.integer.size() > 1) {
			int rhsIndx = rhs.integer.size() - 2;
			long long temp = rhs.integer[rhsIndx] * multiples - r.integer[i-1];
			temp -= base * rem;
			if (temp > 0) {
				long long change = temp;
				change /= (base * rhs.integer[rhsIndx + 1] + rhs.integer[rhsIndx]);
				multiples -= change;
				rem = temp - rhs.integer[rhsIndx] * change; 
				rem -= rhs.integer[rhsIndx + 1] * base * change;
				if (rem > 0) {
					multiples -= 1;
					rem -= rhs.integer[rhsIndx + 1] * base;
					rem -= rhs.integer[rhsIndx];
				}
				rem *= -1;
			}
			else {
				rem = -temp;
			}
		}
		
		// validate (adjusted) estimate against all lower digits, on fail
		// subtract 1 and continue (this is now the valid multiples value)
		int next = i - 2;
		for (int j = rhs.integer.size() - 3; j >= 0; j--) {
			long long temp = rhs.integer[j] * multiples - r.integer[next];
			next--;
			temp -= base * rem;
			if (temp > 0) {
				multiples -= 1;
				break;
			} 
			else {
				rem = -temp;
				if (rem >= base) { break; }
			}
		}

		if (multiples > 0) {
			//std::cout << "multiples is: " << multiples << std::endl;
			int rhsIndex = 0;
			carry = 0;
			for (int j = i - rhs.integer.size() + 1; j <= i; j++) {
				long long temp = rhs.integer[rhsIndex++] * multiples;
				r.integer[j] -= carry;
				if (temp > r.integer[j]) {
					carry = temp / base;
					if (temp - carry * base > r.integer[j]) { carry++; }
					r.integer[j] += base * carry - temp;
				}
				else {
					r.integer[j] -= temp;
					carry = 0;
				}
			}
			carry = r.integer[i];  // carry is left-over from current digit
			//std::cout << "carry is: " << carry << std::endl;
			quotient.integer[quotient.integer.size() - integer.size() + i] = multiples;
		}
		else {
			quotient.integer[quotient.integer.size() - integer.size() + i] = 0;
			carry = r.integer[i];
		}
	}
	// check for trailing zero
	if (quotient.integer[quotient.integer.size() - 1] == 0) {
		quotient.integer.pop_back();
	}
	return quotient;
}
bool bigInt::smaller(std::vector<long long>& d, std::vector<long long>& r, int start){
	if (r.size() - start < d.size()) { return false; }
	bool nextNeedsToBeAsBig = true;
	for (auto it = d.rbegin(); it != d.rend(); it++) {
		if (*it < r[start]) { return true; }
		else if (*it == r[start]) { nextNeedsToBeAsBig = true; }
		else if (*it > r[start] && nextNeedsToBeAsBig) { return false; }
		start--;
	}
	return true;
}
bigInt bigInt::operator^(const bigInt& rhs) const {
	if (rhs > 1) {
		bigInt tracker(2);
		bigInt result = (*this) * (*this);
		while ((tracker + tracker) < rhs) {
			tracker += tracker;
			result *= result;
		}
		for (; tracker < rhs; tracker++) {
			result *= *this;
		}
		return result;
	}
	else if (rhs == 1) { return *this; }
	else if (rhs ==  0) { return 1; }
	else { return 0; }
}
bool bigInt::operator<(const bigInt& rhs) const {
	if (integer.size() < rhs.integer.size()) { return true; }
	else if (integer.size() > rhs.integer.size()) { return false; }
	else {
		for (int i = integer.size() - 1; i >= 0; i--) {
			if (integer[i] < rhs.integer[i]) { return true; }
			else if (integer[i] == rhs.integer[i]) { continue; }
			else { return false; }
		}
		return false;
	}
}
bool bigInt::operator>(const bigInt& rhs) const {
	if (integer.size() > rhs.integer.size()) { return true; }
	else if (integer.size() < rhs.integer.size()) { return false; }
	else {
		for (int i = integer.size() - 1; i >= 0; i--) {
			if (integer[i] > rhs.integer[i]) { return true; }
			else if (integer[i] == rhs.integer[i]) { continue; }
			else { return false; }
		}
		return false;
	}
}
bool bigInt::operator==(const bigInt& rhs) const {
	if (integer.size() != rhs.integer.size()) { return false; }
	if (negative != rhs.negative) { return false; }
	for (int i = 0; i < integer.size(); i++) {
		if (integer[i] != rhs.integer[i]) { return false; }
	}
	return true;
}
bool bigInt::operator!=(const bigInt& rhs) const {
	return !(*this == rhs);
}
bool bigInt::operator>=(const bigInt& rhs) const {
	if (*this > rhs || *this == rhs) { return true; }
	return false;
}
bool bigInt::operator<=(const bigInt& rhs) const {
	if (*this < rhs || *this == rhs) { return true; }
	return false;
}
std::ostream& operator<<(std::ostream &out, const bigInt& i) {
	if (i.negative) { out << "-"; }
	if (i.integer.size() == 0) {
		out << 0;
		return out;
	}
	else {
		out << i.integer[i.integer.size() - 1];
		for (int j = i.integer.size() - 2; j >= 0; j--) {
			out << std::setw(bigInt::digits) << std::setfill('0') << i.integer[j];
		}
		return out;
	}
}
bigInt bigInt::divideByTwo() {
	bigInt newInt(*this);
	long long carry = 0;
	for (int i = newInt.integer.size() - 1; i >= 0; i--) {
		if (newInt.integer[i] % 2 == 0) { 
			newInt.integer[i] /= 2; 
			newInt.integer[i] += carry;
			carry = 0;
		}
		else {
			newInt.integer[i] /= 2;
			newInt.integer[i] += carry;
			carry = 5;
		}
	}
	if (newInt.integer[newInt.integer.size() - 1] == 0) { 
		newInt.integer.pop_back(); 
	}
	return newInt;
}

